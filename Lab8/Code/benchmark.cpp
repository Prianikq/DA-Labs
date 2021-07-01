#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
const double EPS = 1E-9;
using duration_t = std::chrono::microseconds;
int CalculateRank(std::vector<std::vector<double> > a) {
    int n = a.size();
    int m = a[0].size();
    int rank = std::max(n, m);
    std::vector<bool> line_used(n);
    for (int i = 0; i < m; ++i) {
        int j;
        for (j = 0; j < n; ++j) {
            if (!line_used[j] && abs(a[j][i]) > EPS) {
                break;
            }
        }
        if (j == n) {
            --rank;
        }
        else {
            line_used[j] = true;
            for (int p = i + 1; p < m; ++p) {
                a[j][p] /= a[j][i];
            }
            for (int k = 0; k < n; ++k) {
                if (k != j && std::abs(a[k][i]) > EPS) {
                    for (int p = i + 1; p < m; ++p) {
                        a[k][p] -= a[j][p] * a[k][i];
                    }
                }
            }
        }
    }
    return rank;
}

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int n, m;
    std::cin >> m >> n;
    std::vector<std::vector<double> > counts(m, std::vector<double>(n));
    std::vector<std::pair<int, int> > bags(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> counts[i][j];
        }
        std::cin >> bags[i].first;
        bags[i].second = i;
    }
    start = std::chrono::system_clock::now();
    std::sort(bags.begin(), bags.end());
    std::vector<std::vector<double> > matrix;
    std::vector<int> answer;
    for (int i = 0; i < m && answer.size() != n; ++i) {
        matrix.push_back(counts[bags[i].second]);
        if (CalculateRank(matrix) == matrix.size()) {
            answer.push_back(bags[i].second);
        }
        else {
            matrix.pop_back();
        }
    }
    end = std::chrono::system_clock::now();
    int64_t workTime = std::chrono::duration_cast<duration_t>( end - start ).count();
    if (answer.size() != n) {
        std::cout << -1;
    }
    else {
        std::sort(answer.begin(), answer.end());
        for (int i = 0; i < answer.size(); ++i) {
            std::cout << answer[i] + 1 << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Algorithm work time --> " << workTime << " microsec. " << std::endl;
    return 0;
}
