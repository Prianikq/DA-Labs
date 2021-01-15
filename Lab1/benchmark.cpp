#include "vector.hpp"
#include "radix_sort.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
using namespace NMyStd;
bool operator<(const TData& first, const TData& second) {
    return first.Key < second.Key;
}
using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "ms";
int main() {
    TVector<TData> data;
    std::vector<TData> data2;
    TData input;
    while (std::cin >> input.Number >> input.Str) {
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
        data2.push_back(input);
    }
    // Измеряем время работы поразрядной сортировки.
    std::chrono::time_point<std::chrono::system_clock> startTs = std::chrono::system_clock::now();
    RadixSort(data);
    auto endTs = std::chrono::system_clock::now();
    uint64_t radixSortTs = std::chrono::duration_cast<duration_t>( endTs - startTs ).count();
    // Измеряем время работы stl сортировки.
    startTs = std::chrono::system_clock::now();
    std::stable_sort(std::begin(data2), std::end(data2));
    endTs = std::chrono::system_clock::now();
    uint64_t stlSortTs = std::chrono::duration_cast<duration_t>( endTs - startTs ).count();
    std::cout << "Radix sort time: " << radixSortTs << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stlSortTs << DURATION_PREFIX << std::endl;
    return 0;
}
