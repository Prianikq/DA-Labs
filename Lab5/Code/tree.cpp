#include "structures.hpp"
#include <queue>
namespace NMyStd {
    TSuffixTree::TSuffixTree(std::string& word) {
        Word = word;
        int pos = 0;
        int node = 0;
        int size = 1;
        Len.resize(2 * Word.size());
        LPos.resize(2 * Word.size());
        Link.resize(2 * Word.size());
        Edges.resize(2 * Word.size());
        Len[0] = INF;
        for (int i = 0; i < Word.size(); ++i) {
            ++pos;
            int last = 0;
            while (pos > 0) {
                while (pos > Len[Edges[node][Word[i + 1 - pos]]] && Len[Edges[node][Word[i + 1 - pos]]] != INF) {
                    node = Edges[node][Word[i + 1 - pos]];
                    pos -= Len[node];
                }
                int edge = Word[i + 1 - pos];
                int& vertex = Edges[node][edge];
                int symbol = Word[LPos[vertex] + pos - 1];
                if (vertex == 0) {
                    vertex = size++;
                    Len[vertex] = INF;
                    LPos[vertex] = i + 1 - pos;
                    Link[last] = node;
                    last = 0;
                }
                else if (symbol == Word[i]) {
                    Link[last] = node;
                    break;
                }
                else {
                    int newInnerVertex = size++;
                    Len[newInnerVertex] = pos - 1;
                    LPos[newInnerVertex] = LPos[vertex];
                    Link[last] = newInnerVertex;
                    Edges[newInnerVertex][symbol] = vertex;
                    int newLeaf = size++;
                    Len[newLeaf] = INF;
                    LPos[newLeaf] = i;
                    Edges[newInnerVertex][Word[i]] = newLeaf;
                    LPos[vertex] += pos - 1;
                    if (Len[vertex] != INF) {
                        Len[vertex] -= pos - 1;
                    }
                    vertex = newInnerVertex;
                    last = newInnerVertex;
                }
                if (node == 0) {
                    --pos;
                }
                else {
                    node = Link[node];
                }
            }
        }
    }
    void TSuffixTree::Search(std::string& word, std::vector<int>& results) {
        int node = 0;
        int index = 0;
        while (true) {
            int nextVertex = Edges[node][word[index]];
            if (nextVertex == 0) {
                return;
            }
            int begin = LPos[nextVertex];
            int end = LPos[nextVertex] + (Len[nextVertex] == INF ? Word.size() - LPos[nextVertex] - 1:  Len[nextVertex] - 1);
            for (int j = begin; j <= end; ++j) {
                if (Word[j] != word[index]) {
                    return;
                }
                else {
                    ++index;
                    if (index == word.size()) {
                        std::queue<std::pair<int, int> > q;
                        if (Len[nextVertex] == INF) {
                            results.push_back(Word.size() - (index + (end - j)) + 1);
                            return;
                        }
                        q.push(std::make_pair(index + (end - j), nextVertex));
                        while (!q.empty()) {
                            std::pair<int, int> f = q.front();
                            q.pop();
                            if (Len[f.second] == INF) {
                                results.push_back(Word.size() - (Word.size() - LPos[f.second]) - f.first + 1);
                                continue;
                            }
                            for (auto& item : Edges[f.second]) {
                                int depth = f.first;
                                if (Len[item.second] != INF) {
                                    depth += Len[item.second];
                                }
                                q.push(std::make_pair(depth, item.second));
                            }
                        }
                        return;
                    }
                }
            }
            node = nextVertex;
        }
    }
}
