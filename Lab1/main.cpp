#include "vector.hpp"
#include "radix_sort.hpp"
#include <stdio.h>
using namespace NMyStd;
int main() {
    TVector<TData> data;
    TData input;
    while (scanf("%s\t%s\n", input.Number, input.Str) > 0) {
        int len = 0;
        for (int i = 0; i < ALL_NUMBER_DIGITS+EXTRA_SYMBOLS; ++i) {
	        if (input.Number[i] == '\0') {
	            len = i - 1;
	            break;
	        }
	    }
	    long long power = 1;
	    input.Key = 0;
	    while (len != 0) {
	        if (input.Number[len] != '-') {
	            input.Key += (input.Number[len] - '0') * power;
	            power *= 10;
	        }
	        --len;
	    }
        data.PushBack(input);
    }
    RadixSort(data);
    for (int i = 0; i < data.GetSize(); ++i) {
        printf("%s\t%s\n", data[i].Number, data[i].Str);
    }
    return 0;
}
