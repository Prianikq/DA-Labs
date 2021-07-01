#include "kdtree.hpp"
#include <fstream>
#include <cstdio>
#include <iostream>
#include <string>
int main(int argc, char *argv[]) {
    std::string inputFileName;
    std::string outputFileName;
    std::string structFileName;
    std::string typeWork;
    for (int i = 1; i < argc; ++i) {
        std::string check(argv[i]);
        if (i == 1) {
            typeWork = check;
        }
        else if (i % 2 == 0) {
            if (check == "--input") {
                check = std::string(argv[i + 1]);
                inputFileName = check;
            }
            else if (check == "--output") {
                check = std::string(argv[i + 1]);
                outputFileName = check;
            }
            else if (check == "--struct") {
                check = std::string(argv[i + 1]);
                structFileName = check;
            }
            else {
                std::cout << "Error! Wrong program key input!\n";
                return -1;
            }
        }
    }
    if (typeWork != "build" && typeWork != "search") {
        std::cout << "Wrong work key input!\n";
        return -1;
    }
    std::streambuf *cinbuf = std::cin.rdbuf();
    std::streambuf *coutbuf = std::cout.rdbuf();
    if (!inputFileName.empty()) {
        static std::ifstream in(inputFileName);
        std::cin.rdbuf(in.rdbuf());
    }
    int demensions;
    std::cin >> demensions;
    std::vector<NMyStd::TPoint> points;
    std::vector<int> coords(demensions);
    while (std::cin >> coords[0]) {
        for (int i = 1; i < demensions; ++i) {
            std::cin >> coords[i];
        }
        points.push_back(NMyStd::TPoint(coords));
    }
    if (typeWork == "build") {
        NMyStd::TKDTree tree(points);
        if (outputFileName.empty()) {
            tree.ConsoleOutput();
        }
        else {
            std::ofstream out(outputFileName, std::ios::binary);
            tree.SaveInFile(out);
            out.close();
        }
    }
    else {
        if (structFileName.empty()) {
    		std::cout << "Error! No struct file name input!\n";
    		return -1;
    	}
    	if (!outputFileName.empty()) {
            static std::ofstream out(outputFileName);
            std::cout.rdbuf(out.rdbuf());
        }
    	std::ifstream treeStructure(structFileName, std::ios::binary);
    	NMyStd::TKDTree tree(treeStructure);
    	treeStructure.close();
    	for (int i = 0; i < points.size(); ++i) {
    	    NMyStd::TPoint result = tree.Search(points[i]);
    	    std::cout << "Nearest neighbor for ";
    	    points[i].Output();
    	    std::cout << " is ";
    	    result.Output();
    	    std::cout << '\n';
    	}
    	if (!outputFileName.empty()) {
    	    std::cout.rdbuf(coutbuf);
    	}
    }
    if (!inputFileName.empty()) {
        std::cin.rdbuf(cinbuf);
    }
    return 0;
}
