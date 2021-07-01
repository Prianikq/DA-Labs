#include "bigInteger.hpp"
#include <iostream>
#include <gmpxx.h>
#include <chrono>
using duration_t = std::chrono::microseconds;
int main() {
    char operation;
    std::string first, second;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t myBigIntTime = 0, gmpBigIntTime = 0;
    while (std::cin >> first >> second >> operation) {
        start = std::chrono::system_clock::now();
        NMyStd::TBigInteger myFirst(first), mySecond(second), myResult;
        if (operation == '+') {
            myResult = myFirst + mySecond;
        }
        else if (operation == '-') {
            myResult = myFirst - mySecond;
        }
        else if (operation == '*') {
            myResult = myFirst * mySecond;
        }
        else if (operation == '/') {
            myResult = myFirst / mySecond;
        }
        else if (operation == '>') {
            myFirst > mySecond;
        }
        else if (operation == '<') {
            myFirst < mySecond;
        }
        else if (operation == '=') {
            myFirst == mySecond;
        }
        end = std::chrono::system_clock::now();
        myBigIntTime += std::chrono::duration_cast<duration_t>( end - start ).count();
        
        start = std::chrono::system_clock::now();
        mpz_class gmpFirst(first.c_str()), gmpSecond(second.c_str()), gmpResult;
        if (operation == '+') {
            gmpResult = gmpFirst + gmpSecond;
        }
        else if (operation == '-') {
            gmpResult = gmpFirst - gmpSecond;
        }
        else if (operation == '*') {
            gmpResult = gmpFirst * gmpSecond;
        }
        else if (operation == '/') {
            gmpResult = gmpFirst / gmpSecond;
        }
        else if (operation == '>') {
            gmpFirst > gmpSecond;
        }
        else if (operation == '<') {
            gmpFirst < gmpSecond;
        }
        else if (operation == '=') {
            gmpFirst == gmpSecond;
        }
        end = std::chrono::system_clock::now();
        gmpBigIntTime += std::chrono::duration_cast<duration_t>( end - start ).count();
    }
    std::cout << "My TBigInteger work time = " << myBigIntTime << " ms, Gmp library work time = " << gmpBigIntTime << " ms" << std::endl;
    return 0;
}
