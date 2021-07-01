#include "structures.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
using duration_t = std::chrono::microseconds;
int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::string text, pattern;
    std::cin >> text;
    text += "$";
    int64_t suffixTreeBuildTime = 0, suffixArrayBuildTime = 0, suffixTreeSearchTime = 0, suffixArraySearchTime = 0;
    // Building Suffix Tree
    start = std::chrono::system_clock::now();
    NMyStd::TSuffixTree tree(text);
    end = std::chrono::system_clock::now();
    suffixTreeBuildTime += std::chrono::duration_cast<duration_t>( end - start ).count();
    //Building Suffix Array
    start = std::chrono::system_clock::now();
    NMyStd::TSuffixArray array(text);
    end = std::chrono::system_clock::now();
    suffixArrayBuildTime += std::chrono::duration_cast<duration_t>( end - start ).count();
    int count = 1;
    while (std::cin >> pattern) {
        std::vector<int> results1, results2;
        // Suffix Tree Search
        start = std::chrono::system_clock::now();
        tree.Search(pattern, results1);
        end = std::chrono::system_clock::now();
        suffixTreeSearchTime += std::chrono::duration_cast<duration_t>( end - start ).count();
        // Suffix Array Search
        start = std::chrono::system_clock::now();
        array.Search(pattern, results2);
        end = std::chrono::system_clock::now();
        suffixArraySearchTime += std::chrono::duration_cast<duration_t>( end - start ).count();
        if (!results1.empty()) {
            std::sort(results1.begin(), results1.end());
            std::sort(results2.begin(), results2.end());
            if (results1 != results2) {
                std::cout << "ERROR! WRONG ANSWER!" << std::endl;
                return -1;
            }
            /*std::cout << count << ": ";
            for (int i = 0; i < results1.size(); ++i) {
                std::cout << results1[i];
                if (i + 1 != results1.size()) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;*/
        }
        ++count;
    }
    std::cout << "Suffix Tree build time = " << suffixTreeBuildTime << " microsec. " << std::endl;
    std::cout << "Suffix Tree search time = " << suffixTreeSearchTime << " microsec. " << std::endl;
    std::cout << "Suffix Array build time = " << suffixArrayBuildTime  << " microsec. " << std::endl;
    std::cout << "Suffix Array search time = " << suffixArraySearchTime << " microsec. " << std::endl;
}
