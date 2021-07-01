#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using duration_t = std::chrono::microseconds;
void Rec(int n, std::vector<int>& results, std::vector<char>& samples) {
    if (n == 1 || results[n] != 0) {
        return;
    }
    char choice = 1;
    Rec(n - 1, results, samples);
    int minimum = results[n - 1];
    if (n % 2 == 0) {
        Rec(n / 2, results, samples);
        int answer = results[n / 2];
        if (answer < minimum) {
            minimum = answer;
            choice = 2;
        }
    }
    if (n % 3 == 0) {
        Rec(n / 3, results, samples);
        int answer = results[n / 3];
        if (answer < minimum) {
            minimum = answer;
            choice = 3;
        }
    }
    samples[n] = choice;
    results[n] = minimum + n;
}
int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int64_t DPTime, RecursionTime;
    int n;
    std::cin >> n;
    start = std::chrono::system_clock::now();
    std::vector<int> costs1(n + 1);
    std::vector<char> samples1(n + 1);
    for (int i = 2; i <= n; ++i) {
        char choice = 1;
        costs1[i] = costs1[i - 1];
        if (i % 2 == 0 && costs1[i] > costs1[i / 2]) {
            costs1[i] = costs1[i / 2];
            choice = 2;
        }
        if (i % 3 == 0 && costs1[i] > costs1[i / 3]) {
            costs1[i] = costs1[i / 3];
            choice = 3;
        }
        costs1[i] += i;
        samples1[i] = choice;
    }
    end = std::chrono::system_clock::now();
    DPTime = std::chrono::duration_cast<duration_t>( end - start ).count();
    int answer1 = costs1[n];
    std::vector<char> way1;
    int work = n;
    while (work != 1) {
        way1.push_back(samples1[work]);
        if (samples1[work] == 1) {
            work -= 1;
        }
        else if (samples1[work] == 2) {
            work /= 2;
        }
        else if (samples1[work] == 3) {
            work /= 3;
        }
    }
    std::reverse(way1.begin(), way1.end());
    start = std::chrono::system_clock::now();
    std::vector<int> costs2(n + 1);
    std::vector<char> samples2(n + 1);
    Rec(n, costs2, samples2);
    end = std::chrono::system_clock::now();
    RecursionTime = std::chrono::duration_cast<duration_t>( end - start ).count();
    int answer2 = costs2[n];
    std::vector<char> way2;
    work = n;
    while (work != 1) {
        way2.push_back(samples2[work]);
        if (samples2[work] == 1) {
            work -= 1;
        }
        else if (samples2[work] == 2) {
            work /= 2;
        }
        else if (samples2[work] == 3) {
            work /= 3;
        }
    }
    std::reverse(way2.begin(), way2.end());
    if (answer1 != answer2 || way1 != way2) {
        std::cout << "ERROR! ANSWERS DIDN'T MATCH!" << std::endl;
        return -1;
    }
    else {
        std::cout << answer1 << std::endl;
        for (int i = 0; i < way2.size(); ++i) {
            if (way2[i] == 1) {
                std::cout << "-1 ";
            }
            else if (way2[i] == 2) {
                std::cout << "/2 ";
            }
            else {
                std::cout << "/3 ";
            }
        }
        std::cout << std::endl;
        std::cout << "DP work time = " << DPTime << " microsec. " << std::endl;
        std::cout << "Recursion algorithm work time = " << RecursionTime << " microsec. " << std::endl;
    }
    return 0;
}
