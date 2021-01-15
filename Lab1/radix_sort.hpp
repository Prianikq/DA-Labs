#pragma once
#include "vector.hpp"
using namespace NMyStd;
const int SIZE_STR = 65;
const int CODE_CNTR_COUNT_DIGITS = 3;
const int CODE_CITY_COUNT_DIGITS = 3;
const int NUMBER_COUNT_DIGITS = 7;
const int ALL_NUMBER_DIGITS = CODE_CNTR_COUNT_DIGITS + CODE_CITY_COUNT_DIGITS + NUMBER_COUNT_DIGITS;
const int EXTRA_SYMBOLS = 4;
const int COUNT_DIGITS = 10;
struct TData {
    long long Key;
    char Number[ALL_NUMBER_DIGITS + EXTRA_SYMBOLS];
    char Str[SIZE_STR];
};
void RadixSort(TVector<TData>& data) {
    TVector<int> bitValues(COUNT_DIGITS);
    TVector<TData> result(data.GetSize());
    int flag = 0;
    for (int i = ALL_NUMBER_DIGITS - 1; i >= 0; --i) {
        bitValues.Assert(0);
        for (int j = 0; j < data.GetSize(); ++j) {
            if (flag == 0) { 
                long long digit = data[j].Key % COUNT_DIGITS;
                ++bitValues[digit]; 
            }
            else if (flag == 1) { 
                long long digit = result[j].Key % COUNT_DIGITS;
                ++bitValues[digit]; 
            }
        }
        for (int j = 1; j < COUNT_DIGITS; ++j) {
            bitValues[j] += bitValues[j-1];
        }
        for (int j = data.GetSize() - 1; j >= 0; --j) {
            if (flag == 0) { 
                long long digit = data[j].Key % COUNT_DIGITS;
                result[--bitValues[digit]] = data[j]; 
                result[bitValues[digit]].Key /= COUNT_DIGITS;
            }
            else if (flag == 1) { 
                long long digit = result[j].Key % COUNT_DIGITS;
                data[--bitValues[digit]] = result[j]; 
                data[bitValues[digit]].Key /= COUNT_DIGITS;
            }
        }
        flag = (flag ? 0 : 1);
    }
    if (flag == 1) {
        data = result;
    }
}
