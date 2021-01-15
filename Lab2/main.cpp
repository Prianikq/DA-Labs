#include <stdio.h>
#include "btree.hpp"
#include "string.hpp"
int main() {
    TBtree tree;
    char oper[WORD_LENGTH], word1[WORD_LENGTH], word2[WORD_LENGTH];
    unsigned long long value;
    while (scanf("%s", oper) != EOF) {
        if (oper[0] == '+') {
            scanf("%s%llu", word1, &value);
            Convert(word1);
            if (tree.Insert(word1, value) == FAIL) {
                printf("Exist\n");
            }
            else {
                printf("OK\n");
            }
        }
        else if (oper[0] == '-') {
            scanf("%s", word1);
            Convert(word1);
            if (tree.Erase(word1) == FAIL) {
                printf("NoSuchWord\n");
            }
            else {
                printf("OK\n");
            }
        }
        else if (oper[0] == '!') {
            scanf("%s%s", word1, word2);
            if (word1[0] == 'L') {
                
                FILE* readFile =  fopen(word2, "rb");
                if (readFile == nullptr) {
                    printf("ERROR: file %s wasn't opened for reading!\n", word2);
                }
                if (tree.ReadFromFile(readFile) == FAIL) {
                    printf("ERROR: file %s isn't in correct format!\n", word2);
                }
                else {
                    printf("OK\n");
                }
                fclose(readFile);
            }
            else {
                FILE* writeFile = fopen(word2, "wb");
                if (writeFile == nullptr) {
                    printf("ERROR: file %s wasn't opened for writing!\n", word2);
                }
                tree.WriteToFile(writeFile);
                printf("OK\n");
                fclose(writeFile);
            }
        }
        else {
            Convert(oper);
            unsigned long long* result = tree.Search(oper);
            if (result == nullptr) {
                printf("NoSuchWord\n");
            }
            else {
                printf("OK: %llu\n", *result);
            }
        }
    }
}
