#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <set>
const int REQUESTS_COUNT = 100000;
const int OPERATIONS_COUNT = 3;
const int WORD_LENGTH = 3;
const int COUNT_LETTERS = 26;
const int TYPE_LETTER = 2;
const int FILE_NAME_LENGTH = 1;
const int FILE_POSSIBILITY = 98;
const int FILE_RANGE = 100;
const unsigned long long MAX_VALUE = 100000000;
enum Type {INSERT, ERASE, SEARCH, FILE_WORK};
using namespace std;
int main() {
    srand(time(0));
    set<string> files;
    for (int i = 0; i < REQUESTS_COUNT; ++i) {
        int type = rand() % OPERATIONS_COUNT;
        if (type != FILE_WORK) {
            string str(WORD_LENGTH, '0');
            unsigned long long value = rand() % MAX_VALUE;
            for (int i = 0; i < WORD_LENGTH; ++i) {
                int upper = rand() % TYPE_LETTER;
                if (upper == 1) {
                    str[i] = rand() % COUNT_LETTERS + 'A';
                }
                else {
                    str[i] = rand() % COUNT_LETTERS + 'a';
                }
            }
            if (type == INSERT) {
                cout << "+ " << str << " " << value << endl;
            }
            else if (type == ERASE) {
                cout << "- " << str << endl;
            }
            else if (type == SEARCH) {
                cout << str << endl;
            }
        }
        else  {
            int probability = rand() % FILE_RANGE;
            if (probability >= FILE_POSSIBILITY) {
                string file(FILE_NAME_LENGTH, '0');
                for (int i = 0; i < FILE_NAME_LENGTH; ++i) {
                    file[i] = rand() % COUNT_LETTERS + 'a';
                }
                if (files.count(file)) {
                    cout << "! Load " << file << endl;
                }
                else {
                    cout << "! Save " << file << endl;
                    files.insert(file);
                }
            }
            else {
                --i;
            }
        }
    }
}
