#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
#include <functional>
const int MAX_EDGE_COST = 1000000000;
using duration_t = std::chrono::microseconds;
long long EdmondsKarp(const std::vector<std::vector<int> > & edges, std::vector<std::vector<int> > &cF) {
    long long answer = 0;
    bool ok = true;
    int n = edges.size()-1;
    while (ok) {
        ok = false;
        std::queue<int> q;
        std::vector<int> visited(n+1);
        q.push(1);
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            if (t == n) {
                int mini = MAX_EDGE_COST;
                int pos = n;
                while (pos != 1) {
                    mini = std::min(mini, cF[visited[pos]][pos]);
                    pos = visited[pos];
                }
                pos = n;
                while (pos != 1) {
                    cF[visited[pos]][pos] -= mini;
                    cF[pos][visited[pos]] += mini;
                    pos = visited[pos];
                }
                answer += mini;
                ok = true;
                break;
            }
            for (int i = 0; i < edges[t].size(); ++i) {
                if (cF[t][edges[t][i]] != 0 && visited[edges[t][i]] == 0) {
                    visited[edges[t][i]] = t;
                    q.push(edges[t][i]);
                }
            }
        }
    }
    return answer;
}
long long FordFalkersonDFS(const std::vector<std::vector<int> > & edges, std::vector<std::vector<int> > &cF) {
    long long answer = 0;
    bool ok = true;
    int n = edges.size()-1;
    std::function<long long(int, const std::vector<std::vector<int> >&, std::vector<std::vector<int> >&, std::vector<int>&)> dfs = [&dfs, &ok, n, &answer](int v, const std::vector<std::vector<int> > &edges, std::vector<std::vector<int> > &cF, std::vector<int> &visited) {
            if (v == n) {
                int mini = MAX_EDGE_COST;
                int pos = n;
                while (pos != 1) {
                    mini = std::min(mini, cF[visited[pos]][pos]);
                    pos = visited[pos];
                }
                pos = n;
                while (pos != 1) {
                    cF[visited[pos]][pos] -= mini;
                    cF[pos][visited[pos]] += mini;
                    pos = visited[pos];
                }
                answer += mini;
                ok = true;
                return true;
            }
            for (int i = 0; i < edges[v].size(); ++i) {
                if (cF[v][edges[v][i]] != 0 && visited[edges[v][i]] == 0) {
                    visited[edges[v][i]] = v;
                    bool res = dfs(edges[v][i], edges, cF, visited);
                    if (res) {
                        return res;
                    }
                }
            }
            return false;
    };
    while (ok) {
        ok = false;
        std::vector<int> visited(n+1);
        dfs(1, edges, cF, visited);
    }
    return answer;
}
int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int> > edges(n+1);
    std::vector<std::vector<int> > cF1(n+1, std::vector<int>(n+1));
    for (int i = 0; i < m; ++i) {
        int v, u, cost;
        std::cin >> v >> u >> cost;
        edges[v].push_back(u);
        edges[u].push_back(v);
        cF1[v][u] = cost;
    }
    std::vector<std::vector<int> > cF2 = cF1;
    start = std::chrono::system_clock::now();
    long long answer1 = EdmondsKarp(edges, cF1);
    end = std::chrono::system_clock::now();
    int64_t EdmondsKarpTime = std::chrono::duration_cast<duration_t>( end - start ).count();
    start = std::chrono::system_clock::now();
    long long answer2 = FordFalkersonDFS(edges, cF2);
    end = std::chrono::system_clock::now();
    int64_t FordFalkersonDFSTime = std::chrono::duration_cast<duration_t>( end - start ).count();
    if (answer1 != answer2) {
        std::cout << "ERROR! DIFFERENT ANSWERS!" << std::endl;
        return -1;
    }
    std::cout << "Edmonds-Karp method work time = " << EdmondsKarpTime << " microsec. " << std::endl;
    std::cout << "Ford-Falkerson method with dfs work time = " << FordFalkersonDFSTime << " microsec. " << std::endl;
    return 0;
}
