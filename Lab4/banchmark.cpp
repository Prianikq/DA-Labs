#include "search.hpp"
#include <chrono>
using duration_t = std::chrono::microseconds;
int main() {
    std::vector<int> zFunc;
    std::vector<std::string> sample;
    std::vector<int> stringEnd;
    std::vector<std::string> text;
    std::string word;
    std::string textFind, sampleFind;
    word.append(MAX_WORD_LENGTH, 0);
    char c = getchar();
    bool sampleFinish = false;
    bool inputWord = false;
    int index = 0;
    while (c != EOF) {
        if (c == '\n') {
            if (inputWord) {
                if (!sampleFinish) {
                    sample.push_back(word);
                }
                else {
                    text.push_back(word);
                }   
                for (int i = 0; i < index; ++i) {
                    word[i] = 0;
                }
                index = 0;
                inputWord = false;
            }
            if (!sampleFinish) {
                sampleFinish = true;
            }
            else {
                stringEnd.push_back(text.size());
            }
        }
        else if (c == '\t' || c == ' ') {
            if (inputWord) {
                if (!sampleFinish) {
                    sample.push_back(word);
                }
                else {
                    text.push_back(word);
                }
                for (int i = 0; i < index; ++i) {
                    word[i] = 0;
                }
                index = 0;
                inputWord = false;
            }
        }
        else {
            word[index] = c;
            ++index;
            inputWord = true;
        }
        if (c != '\n') {
            if (sampleFinish) {
                textFind.push_back(c);
            }
            else {
                sampleFind.push_back(c);
            }
        }
        c = getchar();
    }
    zFunc.assign(sample.size(), 0);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t zFuncTime = 0, findTime = 0;
    // Working Z-function
    start = std::chrono::system_clock::now();
    CalculateZFunc(sample, zFunc);
    std::vector<TAnswer> ans = FindOccurs(sample, zFunc, text, stringEnd);
    end = std::chrono::system_clock::now();
    zFuncTime = std::chrono::duration_cast<duration_t>( end - start ).count();
    // Working find in std::string
    start = std::chrono::system_clock::now();
    int pos = 0;
    int count = 0;
    while (pos != -1) {
        if (pos != 0) {
            while (pos < textFind.size() && textFind[pos] != ' ') {
                ++pos;
            }
        }
        pos = textFind.find(sampleFind, pos);
        if (pos != -1) {
            ++count;
        }
    }
    end = std::chrono::system_clock::now();
    std::cout << ans.size() << " " << count << std::endl;
    findTime = std::chrono::duration_cast<duration_t>( end - start ).count();
    std::cout << "std::find work time = " << 1.0 * findTime/1000 << "ms, z-function work time = " << 1.0 * zFuncTime/1000 << "ms." << std::endl;
    return 0;
}
