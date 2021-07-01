#include "structures.hpp"
#include <algorithm>
#include <iostream>
namespace NMyStd {
    TSuffixArray::TSuffixArray(TSuffixTree& tree) {
        Word = tree.Word;
        std::vector<std::pair<int,int> > st;
        st.push_back(std::make_pair(0, 0));
        while (!st.empty()) {
            std::pair<int,int> top = st.back();
            st.pop_back();
            if (top.second != 0 && tree.Len[top.second] == TSuffixTree::INF) {
                Array.push_back(Word.size() - (Word.size() - tree.LPos[top.second]) - top.first);
                continue;
            }
            std::map<int,int>::reverse_iterator iter;
            for (iter = tree.Edges[top.second].rbegin(); iter != tree.Edges[top.second].rend(); ++iter) {
                int newDepth = top.first;
                if (tree.Len[iter->second] != TSuffixTree::INF) {
                    newDepth += tree.Len[iter->second];
                }
                if (top.second != 0 || iter->first != '$') {
                     st.push_back(std::make_pair(newDepth, iter->second));
                }
            }
        }
    }
    void TSuffixArray::Search(std::string& word, std::vector<int>& results) {
        int l = -1;
        int r = Array.size();
        bool findSubstr = false;
        while (r - l > 1) {
            int m = (l + r) / 2;
            bool wholeSuffix = true;
            int index = 0;
            for (int i = Array[m]; i < Word.size()-1 && index < word.size(); ++i) {
                if (Word[i] < word[index]) {
                    l = m;
                    wholeSuffix = false;
                    break;
                }
                else if (Word[i] > word[index]) {
                    r = m;
                    wholeSuffix = false;
                    break;
                }
                ++index;
            }
            if (wholeSuffix) {
                l = m;
                if (index == word.size()) {
                    findSubstr = true;
                }
            }
        }
        if (!findSubstr) {
            return;
        }
        int rightAns = l;
        r = l;
        l = -1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            bool wholeSuffix = true;
            int index = 0;
            for (int i = Array[m]; i < Word.size() - 1 && index < word.size(); ++i) {
                if (Word[i] < word[index]) {
                    l = m;
                    wholeSuffix = false;
                    break;
                }
                ++index;
            }
            if (wholeSuffix) {
                if (index == word.size()) {
                    r = m;
                }
                else {
                    l = m;
                }
            }
        }
        int leftAns = r;
        for (int i = leftAns; i <= rightAns; ++i) {
            results.push_back(Array[i] + 1);
        }        
    }
    TSuffixArray::TSuffixArray(std::string& word) {
        Word = word;
        std::vector<int> p(Word.size());
        std::vector<int> cnt((256 > Word.size()? 256 : Word.size()));
        std::vector<int> c(Word.size());
        for (int i = 0; i < Word.size(); ++i) {
	        ++cnt[Word[i]];
	    }
        for (int i = 1; i < 256; ++i) {
	        cnt[i] += cnt[i-1];
	    }
        for (int i = 0; i < Word.size(); ++i) {
	        p[--cnt[Word[i]]] = i;
	    }
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < Word.size(); ++i) {
	        if (Word[p[i]] != Word[p[i-1]]) {
	            ++classes;
	        }
	        c[p[i]] = classes - 1;
        }
        std::vector<int> pn(Word.size());
        std::vector<int> cn(Word.size());
        for (int h = 0; (1<<h) < Word.size(); ++h) {
	        for (int i = 0; i < Word.size(); ++i) {
		        pn[i] = p[i] - (1<<h);
		        if (pn[i] < 0) {
		            pn[i] += Word.size();
		        }
	        }
	        std::fill(cnt.begin(), cnt.end(), 0);
	        for (int i = 0; i < Word.size(); ++i) {
		        ++cnt[c[pn[i]]];
		    }
	        for (int i = 1; i < classes; ++i) {
		        cnt[i] += cnt[i-1];
		    }
	        for (int i = Word.size() - 1; i >= 0; --i) {
		        p[--cnt[c[pn[i]]]] = pn[i];
		    }
	        cn[p[0]] = 0;
	        classes = 1;
	        for (int i=1; i < Word.size(); ++i) {
		        int mid1 = (p[i] + (1<<h)) % Word.size(),  mid2 = (p[i-1] + (1<<h)) % Word.size();
		        if (c[p[i]] != c[p[i-1]] || c[mid1] != c[mid2]) {
			        ++classes;
			    }
		        cn[p[i]] = classes-1;
		    }
		    c = cn;
	    }
	    Array = p;
	}
}
