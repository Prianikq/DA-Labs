#include <map>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
void Convert(string& word) {
    for (int i = 0; i < word.size(); ++i) {
        word[i] -= ('A' <= word[i] && word[i] <= 'Z'? 'A' - 'a' : 0);
    }
}
int main() {
    map<string, map<string, unsigned long long> > storage;
    map<string, unsigned long long> mp;
    string oper, word1, word2;
    unsigned long long value;
    while (cin >> oper) {
        if (oper[0] == '+') {
            cin >> word1 >> value;
            Convert(word1);
            if (mp.count(word1) == 0) {
                mp.insert(make_pair(word1, value));
                cout << "OK" << endl;
            }
            else {
                cout << "Exist" << endl;
            }
        }
        else if (oper[0] == '-') {
            cin >> word1;
            Convert(word1);
            if (mp.count(word1) == 0) {
                cout << "NoSuchWord" << endl;
            }
            else {
                mp.erase(word1);
                cout << "OK" << endl;
            }
        }
    	else if (oper[0] == '!') {
            cin >> word1 >> word2;
            if (word1 == "Load" && storage.count(word2)) {
                mp = storage[word2];
            }
            else {
                storage[word2] = mp;
            }
            cout << "OK" << endl;
        }
        else {
            Convert(oper);
            if (mp.count(oper) == 0) {
                cout << "NoSuchWord" << endl;
            }
            else {
                cout << "OK: " << mp[oper] << endl;
            }
        }
    }
}
