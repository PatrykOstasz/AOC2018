#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "Timer.h"

unsigned countLines(const std::string& filename) {
    ifstream file(filename);
    unsigned result = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
    file.close();
    return result;
}

void loadData(const std::string& filename, vector<string>& data, bool sorted = false) {
    ifstream file(filename);
    string line;
    while (!file.eof()) {
        getline(file, line);
        data.emplace_back(line);
    }
    file.close();
    if (sorted)
        sort(begin(data), end(data));
}

void printData(const vector<string>& data) {
    for (auto v : data) {
        cout << v << endl;
    }
}

#endif // COMMON_H_INCLUDED
