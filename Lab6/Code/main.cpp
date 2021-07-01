#include "bigInteger.hpp"
int main() {
    NMyStd::TBigInteger first, second, result;
    char operation;
    while (std::cin >> first >> second >> operation) {
        if (operation == '+') {
            result = first + second;
            std::cout << result << "\n";
        }
        else if (operation == '-') {
            try {
                result = first - second;
                std::cout << result << "\n";
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (operation == '*') {
            result = first * second;
            std::cout << result << "\n";
        }
        else if (operation == '/') {
            try {
                result = first / second;
                std::cout << result << "\n";
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (operation == '^') {
            try {
                result = Pow(first, second);
                std::cout << result << "\n";
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (operation == '>') {
            std::cout << (first > second ? "true" : "false") << "\n";
        }
        else if (operation == '<') {
            std::cout << (first < second ? "true" : "false") << "\n";
        }
        else if (operation == '=') {
            std::cout << (first == second ? "true" : "false") << "\n";
        }
    }
    return 0;
}
