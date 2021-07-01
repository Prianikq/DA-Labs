#include "kdtree.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
namespace NMyStd {
	long long SquareDist(const TPoint& first, const TPoint& second) {
        long long answer = 0;
        for (int i = 0; i < first.Coords.size(); ++i) {
            answer += 1LL * (first.Coords[i] - second.Coords[i]) * (first.Coords[i] - second.Coords[i]);
        }
        return answer;
    }
    TKDTree::TKDTree(const std::vector<TPoint>& points) {
        int k = points[0].Coords.size();
        int n = points.size();
        std::vector<std::vector<int> > indices(k, std::vector<int>(n));
        std::vector<std::function<bool(const int&, const int&)> > comparators(k);
        Root = nullptr;
        for (int i = 0; i < k; ++i) {
            comparators[i] = [i, k, &points](const int& first, const int& second) {
                int j = i;
                do {
                	if (points[first].Coords[j] != points[second].Coords[j]) {
                		return points[first].Coords[j] < points[second].Coords[j];
                	}
                	j = (j + 1) % k;
                
                } while (j != i);
                return false;
            };
        }
        for (int i = 0; i < k; ++i) {
            std::iota(indices[i].begin(), indices[i].end(), 0);
            std::sort(indices[i].begin(), indices[i].end(), comparators[i]);
        }
        BuildRec(points, indices, comparators, 0, 0, n - 1);
    }
    void Insert(TNode*& root, TNode* newNode) {
        if (root == nullptr) {
            root = newNode;
            return;
        }
        int i = root->Demension;
        do {
            if (root->Key.Coords[i] < newNode->Key.Coords[i]) {
                Insert(root->Right, newNode);
                break;
            }
            else if (root->Key.Coords[i] > newNode->Key.Coords[i]) {
                Insert(root->Left, newNode);
                break;
            }
            i = (i + 1) % root->Key.Coords.size();
        } while (i != root->Demension);  
    }
    void TKDTree::BuildRec(const std::vector<TPoint>& points, std::vector<std::vector<int> > &indices, const std::vector<std::function<bool(const int&, const int&)> >& comparators, const int d, const int l, const int r) {
        int k = points[0].Coords.size();
        int n = points.size();
        int m = (l + r) / 2;
        TNode* newNode = new TNode(points[indices[d][m]]);
        newNode->Demension = d;
        if (r - l + 1 <= 3) {
            if (l <= m - 1) {
                newNode->Left = new TNode(points[indices[d][m - 1]]);
                newNode->Left->Demension = (d + 1) % k;
            }
            if (m + 1 <= r) {
                newNode->Right = new TNode(points[indices[d][m + 1]]);
                newNode->Right->Demension = (d + 1) % k;
            }
            Insert(Root, newNode);
            return;
        }
        else {
            Insert(Root, newNode);
        }
        std::vector<int> buffer(n);
        for (int i = (d + 1) % k; i != d; i = (i + 1) % k) {
            int first = 0;
            int second = 0;
            for (int j = l; j <= r; ++j) {
                if (comparators[d](indices[d][m], indices[i][j]) == comparators[d](indices[i][j], indices[d][m])) {
                    continue;
                }
                else if (comparators[d](indices[d][m], indices[i][j])) {
                    buffer[m + 1 + second] = indices[i][j];
                    ++second;
                }
                else {
                    buffer[l + first] = indices[i][j];
                    ++first;
                }
            }
            for (int j = l; j <= r; ++j) {
                indices[i][j] = buffer[j];
            }
        }
        BuildRec(points, indices, comparators, (d + 1) % k, l, m - 1);
        BuildRec(points, indices, comparators, (d + 1) % k, m + 1, r);
    }
    TPoint TKDTree::Search(const TPoint& point) {
        TNode* answer = NMyStd::Search(Root, point);
        return answer->Key;
    }
    TNode* Search(TNode* root, const TPoint& point) {
        if (root == nullptr) {
            return root;
        }
        int i = root->Demension;
        TNode* firstSearch = nullptr;
        TNode* secondSearch = nullptr;
        do {
            if (root->Key.Coords[i] < point.Coords[i]) {
                firstSearch = root->Right;
                secondSearch = root->Left;
                break;
            }
            else if (root->Key.Coords[i] > point.Coords[i]) {
                firstSearch = root->Left;
                secondSearch = root->Right;
                break;
            }
            i = (i + 1) % root->Key.Coords.size();
        } while (i != root->Demension);
        TNode* temp = Search(firstSearch, point);
        TNode* best = WhichBest(temp, root, point);
        long long radius = SquareDist(point, best->Key);
        long long dist = point.Coords[root->Demension] - root->Key.Coords[root->Demension];
        if (radius >= dist * dist) {
            temp = Search(secondSearch, point);
            best = WhichBest(temp, best, point);
        }
        return best;
    }
    TNode* WhichBest(TNode* first, TNode* second, const TPoint& point) {
    	if (first == nullptr) {
    		return second;
    	}
    	if (second == nullptr) {
    		return first;
    	}
    	long long firstDist = SquareDist(first->Key, point);
    	long long secondDist = SquareDist(second->Key, point);
    	if (firstDist < secondDist) {
    		return first;
    	}
    	else {
    		return second;
    	}
    }
    void TKDTree::ConsoleOutput() {
        NMyStd::ConsoleOutput(Root);
    }
    void TPoint::Output() {
        std::cout << "(";
        for (int i = 0; i < Coords.size(); ++i) {
            std::cout << Coords[i] << (i + 1 == Coords.size()? ")" : ", ");
        }
    }
    void ConsoleOutput(TNode* root) {
        static int l = 0;
        const static int SPACE_WIDTH = 4;
        if (root != nullptr) {
            std::cout << std::setfill(' ') << std::setw(l * SPACE_WIDTH) << ' ';
            std::cout << "\\__";
            root->Key.Output();
            std::cout << '\n';
            ++l;
            ConsoleOutput(root->Left);
            ConsoleOutput(root->Right);
            --l;
        }
    }
    void TKDTree::SaveInFile(std::ofstream& out) {
    	int demensions = Root->Key.Coords.size();
    	out.write((char*)&demensions, sizeof(int));
    	NMyStd::SaveInFile(Root, out);
    }
    void SaveInFile(TNode* root, std::ofstream& out) {
        if (root != nullptr) {
    	    for (int i = 0; i < root->Key.Coords.size(); ++i) {
    	        out.write((char*)&root->Key.Coords[i], sizeof(int));
            }
            out.write((char*)&root->Demension, sizeof(int));
            int haveChild = (root->Left != nullptr ? 1 : 0);
            out.write((char*)&haveChild, sizeof(int));
            SaveInFile(root->Left, out);
            haveChild = (root->Right != nullptr ? 1 : 0);
            out.write((char*)&haveChild, sizeof(int));
            SaveInFile(root->Right, out);
        }
    }
    TKDTree::TKDTree(std::ifstream& in) {
        int demensions; 
        in.read((char*)&demensions, sizeof(int));
        ReadFromFile(Root, in, demensions);
    }
    void ReadFromFile(TNode*& root, std::ifstream& in, const int demensions) {
        std::vector<int> coords(demensions);
        for (int i = 0; i < demensions; ++i) {
            in.read((char*)&coords[i], sizeof(int));
        }
        TPoint point(coords);
        root = new TNode(point);
        int demension, haveChild;
        in.read((char*)&demension, sizeof(int));
        root->Demension = demension;
        in.read((char*)&haveChild, sizeof(int));
        if (haveChild == 1) {
            ReadFromFile(root->Left, in, demensions);
        }
        in.read((char*)&haveChild, sizeof(int));
        if (haveChild == 1) {
            ReadFromFile(root->Right, in, demensions);
        }
    }
}
