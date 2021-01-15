#include <map>
#include <string>
#include "btree.hpp"
#include "string.hpp"
#include <chrono>
void Convert(std::string& word) {
    for (int i = 0; i < word.size(); ++i) {
        word[i] -= ('A' <= word[i] && word[i] <= 'Z'? 'A' - 'a' : 0);
    }
}
using duration_t = std::chrono::microseconds;
int main() {
    std::map<std::string, unsigned long long> mp;
    TBtree tree;
    unsigned long long value;
    char word[WORD_LENGTH], oper[WORD_LENGTH];
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t mapTime = 0, btreeTime = 0;
    while (scanf("%s", oper) != EOF) {
        if (oper[0] == '+') {
            scanf("%s%llu", word, &value);
            Convert(word);
            {
                std::string wordStr(word);
                start = std::chrono::system_clock::now();
                mp.insert(make_pair(wordStr, value));
                end = std::chrono::system_clock::now();
                mapTime += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {

                start = std::chrono::system_clock::now();
                tree.Insert(word, value);
                end = std::chrono::system_clock::now();
                btreeTime += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
        else if (oper[0] == '-') {
            scanf("%s", word);
            Convert(word);
            {
                std::string wordStr(word);
                start = std::chrono::system_clock::now();
                mp.erase(wordStr);
                end = std::chrono::system_clock::now();
                mapTime += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                tree.Erase(word);
                end = std::chrono::system_clock::now();
                btreeTime += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
        else {
            Convert(oper);
            {
                std::string operStr(oper);
                start = std::chrono::system_clock::now();
                mp.count(operStr);
                end = std::chrono::system_clock::now();
                mapTime += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
            {
                start = std::chrono::system_clock::now();
                tree.Search(oper);
                end = std::chrono::system_clock::now();
                btreeTime += std::chrono::duration_cast<duration_t>( end - start ).count();
            }
        }
    }
    printf("std::map work time = %ld ms, btree work time = %ld ms.\n", mapTime, btreeTime);
}
