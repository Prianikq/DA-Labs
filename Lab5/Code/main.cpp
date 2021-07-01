#include "structures.hpp"
#include <iostream>
#include <algorithm>
int main() {
    std::string text, pattern;
    std::cin >> text;
    text += "$";
    NMyStd::TSuffixTree tree(text);
    NMyStd::TSuffixArray array(tree);
    int count = 1;
    while (std::cin >> pattern) {
        std::vector<int> results;
        array.Search(pattern, results);
        if (!results.empty()) {
            std::sort(results.begin(), results.end());
            std::cout << count << ": ";
            for (int i = 0; i < results.size(); ++i) {
                std::cout << results[i];
                if (i + 1 != results.size()) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        ++count;
    }
}
