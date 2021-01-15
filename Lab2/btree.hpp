#pragma once
#include "node.hpp"
class TBtree {
    public :
        TBtree();
        ~TBtree();
        unsigned long long* Search(char* const);
        Result Insert(char* const, const unsigned long long&);
        Result Erase(char* const);
        void Print();
        void WriteToFile(FILE* const file);
        Result ReadFromFile(FILE* const file);
    private :
        TNode* Node;
};
TBtree::TBtree() {
    Node = new TNode;
}
TBtree::~TBtree() {
    delete Node;
}
unsigned long long* TBtree::Search(char* const key) {
    return ::Search(Node, key);    
}
Result TBtree::Insert(char* const key, const unsigned long long& value) {
    return ::Insert(Node, key, value);
}
Result TBtree::Erase(char* const key) {
    return ::EraseInRoot(Node, key);
}
void TBtree::Print() {
    return ::Print(Node, 0);
}
void TBtree::WriteToFile(FILE* const file) {
    ::WriteToFile(Node, file);
}
Result TBtree::ReadFromFile(FILE* const file) {
    TNode* newNodeTree = new TNode;
    if (::ReadFromFile(newNodeTree, file) == FAIL || feof(file)) {
        delete newNodeTree;
        return FAIL;
    }
    int check;
    if (fread(&check, sizeof(int), 1, file) > 0) {
        delete newNodeTree;
        return FAIL;
    }
    delete Node;
    Node = newNodeTree;
    return SUCCESS;
}
