#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
const int MAX_EDGE_COST = 1000000000;
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
int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int> > edges(n+1);
    std::vector<std::vector<int> > cF(n+1, std::vector<int>(n+1));
    for (int i = 0; i < m; ++i) {
        int v, u, cost;
        std::cin >> v >> u >> cost;
        edges[v].push_back(u);
        edges[u].push_back(v);
        cF[v][u] = cost;
    }
    long long answer = EdmondsKarp(edges, cF);
    std::cout << answer << std::endl;
    return 0;
}
