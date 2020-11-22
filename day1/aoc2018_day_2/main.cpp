#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Timer.h"

using namespace std;

void solution();
string solution2(std::vector<string>& vec);
pair<bool, bool> processIdString(const string& id);
unsigned checksum(unsigned twos, unsigned threes);

int main() {
    solution();
    return 0;
}

void solution() {
    Timer t;
    unsigned twoCount = 0, threeCount = 0;
    pair<bool, bool> idsFound;

    vector<string> ids;
    ids.reserve(250);

    string tempId = "";
    ifstream file("input2.txt");
    while(!file.eof()) {
        file >> tempId;
        idsFound = processIdString(tempId);
        ids.emplace_back(tempId);

        twoCount+=static_cast<unsigned>(idsFound.first);
        threeCount+=static_cast<unsigned>(idsFound.second);
    }
    cout << "checksum equals: " << checksum(twoCount, threeCount) << endl;
    cout << "found id: " << solution2(ids) << endl;
}

pair<bool, bool> processIdString(const string& id) {
    pair<bool, bool> result {false, false};
    unordered_multiset<char> id_string(begin(id), end(id));

    for (auto id_elem : id_string) {
        if (id_string.count(id_elem) == 2 and !result.first) {
            result.first = true;
        } else if (id_string.count(id_elem) == 3 and !result.second) {
            result.second = true;
        }
    }

    return result;
}

unsigned checksum(unsigned twos, unsigned threes) {
    return twos*threes;
}

string solution2(std::vector<string>& vec) {
    vector<char> diffs;
    unsigned idCharIndex = 0;
    unsigned idStringIndex = 0;

    sort(begin(vec), end(vec));
    for (unsigned i = 0; i < vec.size()-1; ++i) {
        for(unsigned j = 0; j < vec[i].size(); ++j) {
            if (vec[i][j] != vec[i+1][j]){
                diffs.emplace_back(vec[i][j]);
                idCharIndex = j;
            }
        }
        if (diffs.size() == 1) {
            idStringIndex = i;
            break;

        }
        diffs.clear();
    }
    string foundString = vec[idStringIndex];
    char foundChar = vec[idStringIndex][idCharIndex];
    foundString.erase(remove(begin(foundString), end(foundString), foundChar));

    return foundString;
}
