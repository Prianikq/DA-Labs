#include "kdtree.hpp"
#include <chrono>
#include <iostream>
using duration_t = std::chrono::microseconds;
int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int demsInStruct, count, demsInSearch;
    std::cin >> demsInStruct >> count;
    std::vector<NMyStd::TPoint> points;
    std::vector<int> coords1(demsInStruct);
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < coords1.size(); ++j) {
            std::cin >> coords1[j];
        }
        points.push_back(NMyStd::TPoint(coords1));
    }
    start = std::chrono::system_clock::now();
    NMyStd::TKDTree tree(points);
    end = std::chrono::system_clock::now();
    int64_t TKDTreeBuildTime = std::chrono::duration_cast<duration_t>( end - start ).count();
    std::cin >> demsInSearch >> count;
    std::vector<int> coords2(demsInSearch);
    int TKDTreeSearchTime = 0;
    int TrivialAlgoSearchTime = 0;
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < coords2.size(); ++j) {
            std::cin >> coords2[j];
        }
        NMyStd::TPoint point(coords2);
        // Trivial search algorithm
        start = std::chrono::system_clock::now();
        std::vector<NMyStd::TPoint> answers(1, points[0]);
        for (int j = 1; j < points.size(); ++j) {
            long long best = SquareDist(answers[0], point);
            long long newDist = SquareDist(points[j], point);
            if (best > newDist) {
                answers.clear();
                answers.push_back(points[j]);
            }
            else if (best == newDist) {
                answers.push_back(points[j]);
            }
        }
        end = std::chrono::system_clock::now();
        TrivialAlgoSearchTime += std::chrono::duration_cast<duration_t>( end - start ).count();
        // K-d tree search algorithm
        start = std::chrono::system_clock::now();
        NMyStd::TPoint answer = tree.Search(point);
        end = std::chrono::system_clock::now();
        TKDTreeSearchTime += std::chrono::duration_cast<duration_t>( end - start ).count();
        bool OK = false;
        for (int j = 0; j < answers.size() && !OK; ++j) {
        	bool equals = true;
        	for (int k = 0; k < answer.Coords.size() && equals; ++k) {
        		if (answer.Coords[k] != answers[j].Coords[k]) {
        			equals = false;
        		}
        	}
            if (equals) {
                OK = true;
            }
        }
        if (!OK) {
            std::cout << "Error! Wrong answer in test ";
            point.Output();
            std::cout << "\n";
        }
    }
    std::cout << "K-d tree build time --> " << TKDTreeBuildTime << " microsec.\n";
    std::cout << "K-d tree summary search time --> " << TKDTreeSearchTime << " microsec.\n";
    std::cout << "Trivial algorithm search time --> " << TrivialAlgoSearchTime << " microsec.\n";
}
