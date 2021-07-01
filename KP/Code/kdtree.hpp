#pragma once
#include <vector>
#include <functional>
#include <fstream>
#include <iostream>
namespace NMyStd {
	struct TPoint {
        TPoint(const std::vector<int> &coords): Coords(coords) {};
        void Output();
        std::vector<int> Coords;
    };
    long long SquareDist(const TPoint& first, const TPoint& second);
    struct TNode {
        TNode(const TPoint key): Key(key) {
            Demension = 0;
            Left = nullptr;
            Right = nullptr;
        }
        ~TNode() {
            if (Left != nullptr) {
                delete Left;
            }
            if (Right != nullptr) {
                delete Right;
            }
        }
        TPoint Key;
        int Demension;
        TNode* Left;
        TNode* Right;
    };
    void Insert(TNode*& root, TNode* key);
    TNode* Search(TNode* root, const TPoint& point);
    void ConsoleOutput(TNode* root);
    TNode* WhichBest(TNode* first, TNode* second, const TPoint& point);
    void SaveInFile(TNode* root, std::ofstream& out);
    void ReadFromFile(TNode*& root, std::ifstream& in, const int demensions);
    class TKDTree {
        public:
            TKDTree(const std::vector<TPoint>& points);
            TKDTree(std::ifstream& in);
            ~TKDTree() {
                if (Root != nullptr) {
                    delete Root;
                }
            }
            TPoint Search(const TPoint& point);
            void ConsoleOutput();
            void SaveInFile(std::ofstream& out);
        private:
            TNode* Root;
            void BuildRec(const std::vector<TPoint>& points, std::vector<std::vector<int> > &indices, const std::vector<std::function<bool(const int&, const int&)> >& comparators, const int d, const int l, const int r);
    };
}

