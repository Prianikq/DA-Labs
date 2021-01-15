#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;
const int SIZE_STR = 10;
const int CODE_CNTR_COUNT_DIGITS = 1;
const int CODE_CITY_COUNT_DIGITS = 3;
const int NUMBER_COUNT_DIGITS = 7;
const int ALL_NUMBER_DIGITS = CODE_CNTR_COUNT_DIGITS + CODE_CITY_COUNT_DIGITS + NUMBER_COUNT_DIGITS;
const int EMPTY_STRING = 900;
const int END_STR = 95;
const int COUNT_DIGITS = 10;
const int COUNT_DIF_SYMBOLS = 74;
const int MAX_RAND = 1000;
int main() {
    srand(time(0));
    int count;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        int emptyString = rand() % MAX_RAND;
        if (emptyString > EMPTY_STRING) { 
            cout << endl; 
            continue; 
        }
        int first = rand() % CODE_CNTR_COUNT_DIGITS +1;
        cout << "+";
        for (int j = 0; j < first; ++j) {
	        int num = rand() % COUNT_DIGITS;
	        cout << num;
	    }   
	    cout << "-";
	    for (int j = 0; j < CODE_CITY_COUNT_DIGITS; ++j) {
	        int num = rand() % COUNT_DIGITS;
	        cout << num;
	    }
	    cout << "-";
	    for (int j = 0; j < NUMBER_COUNT_DIGITS; ++j) {
	        int num = rand() % COUNT_DIGITS;
	        cout << num;
	    }
	    cout << "\t";
	    bool skipPos = false;
	    for (int j = 0; j < SIZE_STR; ++j) {
	        if (!skipPos && j > 0) {
	            int skip = rand() % 100;
	            if (skip > END_STR) skipPos = true;
	        }
	        if (skipPos) cout << "\0";
	        else {
	            int symbol = rand() % COUNT_DIF_SYMBOLS;
	            char output = symbol + '0';
	            cout << output;
	        }
        }
        cout << endl;
    }
}
