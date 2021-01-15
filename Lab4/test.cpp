#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <map>
using namespace std;
const int SAMPLE_COUNT_WORDS = 10;
const int TEXT_COUNT_STRINGS = 1;
const int TEXT_MAX_COUNT_WORDS = 1000000;
const int TEXT_MAX_WORD_LENGTH = 2;
const int COUNT_LETTERS = 3;
const int OPTIONS_WORD = 100;
const int IS_SAMPLE = 90;
const int DIFF_WORDS = 9;
int count = 0;
void adder(string word, map<int, string>& alhpabit) {
    if (word.size() == TEXT_MAX_WORD_LENGTH) {
        alhpabit[count] = word;
        ++count;
        return;
    }
    for (int i = 0; i < COUNT_LETTERS; ++i) {
        string check(1, i + 'a');
        string ans = word + check;
        adder(ans, alhpabit);
    }
}
int main() {
    srand(time(0));
    map<int, string> alhpabit;
    string sample = "";
    adder(sample, alhpabit);
    for (int i = 0; i < SAMPLE_COUNT_WORDS; ++i) {
        int choice = rand() % DIFF_WORDS;
        sample = sample + (sample.size() == 0 ? "" : " ") + alhpabit[choice];
    }
    cout << sample << endl;
    for (int i = 0; i < TEXT_COUNT_STRINGS; ++i) {
        for (int j = 0; j < TEXT_MAX_COUNT_WORDS; ++j) {
            int choice = rand() % OPTIONS_WORD;
            if (choice > IS_SAMPLE) {
                cout << sample << " ";
                continue;
            }
            choice = rand() % DIFF_WORDS;
            cout << alhpabit[choice] << " ";
        }
        cout << endl;
    }
    return 0;
}
