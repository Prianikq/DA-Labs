#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
namespace NMyStd {
    class TSuffixTree {
        public:
            friend class TSuffixArray;
            static const int INF = -1;
            TSuffixTree(std::string&);
            void Search(std::string&, std::vector<int>&);
        private:
            std::vector<int> Len;
            std::vector<int> LPos;
            std::vector<int> Link;
            std::vector<std::map<int, int> > Edges;
            std::string Word;
    };
    class TSuffixArray {
        public:
            TSuffixArray(std::string&);
            TSuffixArray(TSuffixTree&);
            void Search(std::string&, std::vector<int>&);
        private:
            std::vector<int> Array;  
            std::string Word;
    };
}
