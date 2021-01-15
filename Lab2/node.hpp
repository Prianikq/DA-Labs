#pragma once
#include "string.hpp"
#include <stdio.h>
template<class T>
void Insert(T* array[], int& count, T* elem, const int index) {
    for (int i = count; i > index; --i) {
        array[i] = array[i - 1];
    }
    array[index] = elem;
    ++count;
}
template<class T>
void Delete(T* array[], int& count, const int index) {
    for (int i = index; i < count - 1; ++i) {
        array[i] = array[i + 1];
    }
    array[count - 1] = nullptr;
    --count;
}
const int WORD_LENGTH = 257;
struct TItem {
    TItem();
    ~TItem();
    char* Key;
    unsigned long long* Value;
};
TItem::TItem() {
    Key = new char[WORD_LENGTH];
    for (int i = 0; i < WORD_LENGTH; ++i) {
        Key[i] = '\0';
    }
    Value = new unsigned long long;
}
TItem::~TItem() {
    delete[] Key;
    delete Value;
}
int BinSearch(TItem* array[], const int& count, char* key) {
    int beg = -1;
    int end = count;
    while (end - beg > 1) {
        int mid = (beg + end) / 2;
        if (StrCompare(key, array[mid]->Key) == LESS) {
            end = mid;
        }
        else {
            beg = mid;
        }
    }
    return beg;
}
const int TREE_DEGREE = 8;
const int MAX_DATA_COUNT = 2*TREE_DEGREE-1;
const int MIN_DATA_COUNT = TREE_DEGREE-1;
const int MAX_NODE_COUNT = 2*TREE_DEGREE;
const int MIN_NODE_COUNT = TREE_DEGREE;
enum Result { SUCCESS, FAIL };
struct TNode {
    TNode();
    ~TNode();
    TNode* NodeArray[MAX_NODE_COUNT];
    TItem* DataArray[MAX_DATA_COUNT];
    bool IsLeaf;
    int NodesCnt;
    int DataCnt;
};

TNode::TNode() {
    IsLeaf = true;
    NodesCnt = 0;
    DataCnt = 0;
    for (int i = 0; i < MAX_DATA_COUNT; ++i) {
        DataArray[i] = nullptr;
        NodeArray[i] = nullptr;
    }	
    NodeArray[MAX_NODE_COUNT - 1] = nullptr;
}
TNode::~TNode() {
    for (int i = 0; i < MAX_DATA_COUNT; ++i) {
        if (DataArray[i] != nullptr) {
            delete DataArray[i];
            DataArray[i] = nullptr;
        }
        if (NodeArray[i] != nullptr) {
            delete NodeArray[i];
            NodeArray[i] = nullptr;
        }
    }
    if (NodeArray[MAX_NODE_COUNT - 1] != nullptr) {
        delete NodeArray[MAX_NODE_COUNT - 1];
        NodeArray[MAX_NODE_COUNT - 1] = nullptr;
    }
}
void Print(TNode* node, int depth) {
    if (node != nullptr) {
        for (int i = 0; i < node->DataCnt; ++i) {
            Print(node->NodeArray[i], depth + 1);
            for (int j = 0; j < depth * 4; ++j) {
                printf(" ");
            }
            printf("%s %llu\n", node->DataArray[i]->Key, *node->DataArray[i]->Value);
        }
        Print(node->NodeArray[node->DataCnt], depth + 1);
    }
}
unsigned long long* Search(TNode* node, char* const key) {
    int pos = BinSearch(node->DataArray, node->DataCnt, key);
    if (pos >= 0 && StrCompare(node->DataArray[pos]->Key, key) == EQUALS) {
        return node->DataArray[pos]->Value;
    }
    else if (node->IsLeaf) {
        return nullptr;
    }
    else {
        ++pos;
        return Search(node->NodeArray[pos], key);
    }
}
void SplitChild(TNode* node, const int& index) {
    TNode* newNode = new TNode;
    newNode->DataCnt = MIN_DATA_COUNT;
    newNode->NodesCnt = (node->NodeArray[index]->IsLeaf ? 0 : MIN_NODE_COUNT);
    newNode->IsLeaf = node->NodeArray[index]->IsLeaf;
    for (int i = 0; i < MIN_DATA_COUNT; ++i) {
        newNode->DataArray[i] = node->NodeArray[index]->DataArray[TREE_DEGREE + i];
        node->NodeArray[index]->DataArray[TREE_DEGREE + i] = nullptr;
    }
    if (!node->NodeArray[index]->IsLeaf) {
        for (int i = 0; i < MIN_NODE_COUNT; ++i) {
            newNode->NodeArray[i] = node->NodeArray[index]->NodeArray[TREE_DEGREE + i];
            node->NodeArray[index]->NodeArray[TREE_DEGREE + i] = nullptr;
        }
    }
    Insert(node->DataArray, node->DataCnt, node->NodeArray[index]->DataArray[MIN_DATA_COUNT], index);
    node->NodeArray[index]->DataArray[MIN_DATA_COUNT] = nullptr;
    Insert(node->NodeArray, node->NodesCnt, newNode, index + 1);
    node->NodeArray[index]->DataCnt = MIN_DATA_COUNT;
    node->NodeArray[index]->NodesCnt = (node->NodeArray[index]->IsLeaf ? 0 : MIN_NODE_COUNT);
}
void MergeChild(TNode* node, const int& big, const int& les) {
    Insert(node->NodeArray[big]->DataArray, node->NodeArray[big]->DataCnt, node->DataArray[big], node->NodeArray[big]->DataCnt);
    node->DataArray[big] = nullptr;
    for (int j = 0; j < node->NodeArray[les]->DataCnt; ++j) {
        node->NodeArray[big]->DataArray[node->NodeArray[big]->DataCnt + j] = node->NodeArray[les]->DataArray[j];
        node->NodeArray[les]->DataArray[j] = nullptr;
    }
    if (!node->NodeArray[big]->IsLeaf) {
        for (int j = 0; j < node->NodeArray[les]->NodesCnt; ++j) {
            node->NodeArray[big]->NodeArray[node->NodeArray[big]->NodesCnt + j] = node->NodeArray[les]->NodeArray[j];
            node->NodeArray[les]->NodeArray[j] = nullptr;
        }
    }
    node->NodeArray[big]->DataCnt += node->NodeArray[les]->DataCnt;
    node->NodeArray[big]->NodesCnt += node->NodeArray[les]->NodesCnt;
    Delete(node->DataArray, node->DataCnt, big);
    delete node->NodeArray[les];
    Delete(node->NodeArray, node->NodesCnt, les);
}
Result InsertNonFull(TNode* node, char* const key, const unsigned long long& value) {
    int pos = BinSearch(node->DataArray, node->DataCnt, key);
    if (pos >= 0 && StrCompare(node->DataArray[pos]->Key, key) == EQUALS) {
        return FAIL;
    }
    ++pos;
    if (node->IsLeaf) {
        TItem* insertItem = new TItem;
        Assign(insertItem->Key, key);
        *insertItem->Value = value;
        Insert(node->DataArray, node->DataCnt, insertItem, pos);
        return SUCCESS;
    }
    else {
        if (node->NodeArray[pos]->DataCnt == MAX_DATA_COUNT) {
            SplitChild(node, pos);
            if (StrCompare(node->DataArray[pos]->Key,  key) == LESS) {
                ++pos;
            }
            else if (StrCompare(node->DataArray[pos]->Key, key) == EQUALS) {
                return FAIL;
            }
        }	
        return InsertNonFull(node->NodeArray[pos], key, value);
    }
}
Result Insert(TNode*& node, char* const key, const unsigned long long& value) {
    if (node->DataCnt == MAX_DATA_COUNT) {
        TNode* newRoot = new TNode;
        newRoot->IsLeaf = false;
        newRoot->NodeArray[0] = node;
        newRoot->NodesCnt++;
        node = newRoot;
        SplitChild(node, 0);
    }
    return InsertNonFull(node, key, value);
}
Result Erase(TNode* node, char* const key) {
    if (node->IsLeaf) {
        int pos = BinSearch(node->DataArray, node->DataCnt, key);
        if (pos >= 0 && StrCompare(node->DataArray[pos]->Key, key) == EQUALS) {
            delete node->DataArray[pos];
            node->DataArray[pos] = nullptr;
            Delete(node->DataArray, node->DataCnt, pos);
            return SUCCESS;
        }
        return FAIL;
    }	
    else {
        int pos = BinSearch(node->DataArray, node->DataCnt, key);
        if (pos >= 0 && StrCompare(key, node->DataArray[pos]->Key) == EQUALS) {
            if (node->NodeArray[pos]->DataCnt > MIN_DATA_COUNT) {
                TNode* search = node->NodeArray[pos];
                while (!search->IsLeaf) {
                    search = search->NodeArray[search->NodesCnt - 1];
                }
                Assign(node->DataArray[pos]->Key, search->DataArray[search->DataCnt - 1]->Key);
                *node->DataArray[pos]->Value = *search->DataArray[search->DataCnt - 1]->Value;
                return Erase(node->NodeArray[pos], node->DataArray[pos]->Key);
            }	
            else if (node->NodeArray[pos + 1]->DataCnt > MIN_DATA_COUNT) {
                TNode* search = node->NodeArray[pos + 1];
                while (!search->IsLeaf) {
                    search = search->NodeArray[0];
                }
                Assign(node->DataArray[pos]->Key, search->DataArray[0]->Key);
                *node->DataArray[pos]->Value = *search->DataArray[0]->Value;
                return Erase(node->NodeArray[pos + 1], node->DataArray[pos]->Key);
            }
            else {
                MergeChild(node, pos, pos + 1);
                return Erase(node->NodeArray[pos], key);
            }
        }
        else {
            ++pos;
            if (node->NodeArray[pos]->DataCnt > MIN_DATA_COUNT) {
                return Erase(node->NodeArray[pos], key);
            }
            if (pos > 0 && node->NodeArray[pos - 1]->DataCnt > MIN_DATA_COUNT) {
                Insert(node->NodeArray[pos]->DataArray, node->NodeArray[pos]->DataCnt, node->DataArray[pos - 1], 0);
                if (!node->NodeArray[pos - 1]->IsLeaf) {
                    Insert(node->NodeArray[pos]->NodeArray, node->NodeArray[pos]->NodesCnt, node->NodeArray[pos - 1]->NodeArray[node->NodeArray[pos - 1]->NodesCnt - 1], 0);
                    Delete(node->NodeArray[pos - 1]->NodeArray, node->NodeArray[pos - 1]->NodesCnt, node->NodeArray[pos - 1]->NodesCnt - 1);
                }
                node->DataArray[pos - 1] = node->NodeArray[pos - 1]->DataArray[node->NodeArray[pos - 1]->DataCnt-1];
                Delete(node->NodeArray[pos - 1]->DataArray, node->NodeArray[pos - 1]->DataCnt, node->NodeArray[pos - 1]->DataCnt - 1);
                return Erase(node->NodeArray[pos], key);
            }
            else if (pos < node->NodesCnt - 1 && node->NodeArray[pos + 1]->DataCnt > MIN_DATA_COUNT) {
                Insert(node->NodeArray[pos]->DataArray, node->NodeArray[pos]->DataCnt, node->DataArray[pos], node->NodeArray[pos]->DataCnt);
                if (!node->NodeArray[pos + 1]->IsLeaf) {
                    Insert(node->NodeArray[pos]->NodeArray, node->NodeArray[pos]->NodesCnt, node->NodeArray[pos + 1]->NodeArray[0], node->NodeArray[pos]->NodesCnt);
                    Delete(node->NodeArray[pos + 1]->NodeArray, node->NodeArray[pos + 1]->NodesCnt, 0);
                }
                node->DataArray[pos] = node->NodeArray[pos + 1]->DataArray[0];
                Delete(node->NodeArray[pos + 1]->DataArray, node->NodeArray[pos + 1]->DataCnt, 0);
                return Erase(node->NodeArray[pos], key);
            }
            else {
                if (pos > 0) {
                    MergeChild(node, pos - 1, pos);
                    return Erase(node->NodeArray[pos - 1], key);
                }
                else {
                    MergeChild(node, pos, pos + 1);
                    return Erase(node->NodeArray[pos], key);
                }
            }
        }
    }
}
Result EraseInRoot(TNode*& node, char* const key) {
    if (node->DataCnt == 1 && !node->IsLeaf && node->NodeArray[0]->DataCnt <= MIN_DATA_COUNT && node->NodeArray[1]->DataCnt <= MIN_DATA_COUNT) {
        TNode* newRoot = node->NodeArray[0];
        MergeChild(node, 0, 1);
        node->NodeArray[0] = nullptr;
        delete node;
        node = newRoot;
    }
    return Erase(node, key);
}
Result ReadFromFile(TNode* const node, FILE* const file) {
    fread(&node->NodesCnt, sizeof(int), 1, file);
    fread(&node->DataCnt, sizeof(int), 1, file);
    if (node->NodesCnt < 0 || node->NodesCnt > MAX_NODE_COUNT || node->DataCnt < 0 || node->DataCnt > MAX_DATA_COUNT) {
        return FAIL;
    }
    node->IsLeaf = (node->NodesCnt == 0? true : false);
    for (int i = 0; i < node->DataCnt; ++i) {
        node->DataArray[i] = new TItem;
        fread(node->DataArray[i]->Key, sizeof(char), WORD_LENGTH, file);
        fread(node->DataArray[i]->Value, sizeof(unsigned long long), 1, file);
    }
    for (int i = 0; i < node->NodesCnt; ++i) {
        node->NodeArray[i] = new TNode;
        ReadFromFile(node->NodeArray[i], file);
    }
    return SUCCESS;
}
void WriteToFile(TNode* const node, FILE* const file) {
    fwrite(&node->NodesCnt, sizeof(int), 1, file);
    fwrite(&node->DataCnt, sizeof(int), 1, file);
    for (int i = 0; i < node->DataCnt; ++i) {
        fwrite(node->DataArray[i]->Key, sizeof(char), WORD_LENGTH, file);
        fwrite(node->DataArray[i]->Value, sizeof(unsigned long long), 1, file);
    }
    for (int i = 0; i < node->NodesCnt; ++i) {
        WriteToFile(node->NodeArray[i], file);
    }
}
