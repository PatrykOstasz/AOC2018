#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_set>

#include "../Timer.h"

using namespace std;

void loadData(const string& filename, string& input) {
    ifstream file(filename);
    file >> input;
    file.close();
}

void createPatterns(string& patterns) {
    stringstream ss;
    unsigned asciiLetterOffset = 32;
    for (char i = 'A'; i <= 'Z'; ++i){
        ss << i << char(i+asciiLetterOffset) << " " << char(i+asciiLetterOffset) << i<<" ";
    }
    patterns = ss.str();
}


unsigned findMatch(unsigned lb, unsigned ub, const string& patterns, const string_view& data, stack<unsigned>& unitIndices) {
    char searchPair[] = {data[lb], data[ub], '\0'};
    string searchString(searchPair);
    if ((patterns.find(searchString) != string::npos)) {
        if (ub == data.size()-1 or unitIndices.empty()) return ub + 1;
        lb = unitIndices.top();
        unitIndices.pop();
        return findMatch(lb, ub + 1, patterns, data, unitIndices);
    }
    unitIndices.push(lb);
    return ub;
}

unsigned getSolutionPart1(const string_view& data, const string& patterns) {
    //Timer t;
    stack<unsigned> polymerUnitsIndices;
    unsigned indexStart = 0;
    while(indexStart < data.size()-1) {
        unsigned iBegin = indexStart;
        indexStart = findMatch(iBegin, iBegin+1, patterns, data, polymerUnitsIndices);
    }
    if (polymerUnitsIndices.size() % 2 != 0) return polymerUnitsIndices.size() + 1;
    return polymerUnitsIndices.size();
}

unsigned getSolutionPart2(const string& data, const string& pattern) {
    vector<unsigned> polymerSizes;
    polymerSizes.reserve(26);

    string inputDataCopy;
    inputDataCopy.reserve(data.size());
    for (auto i = 0; i < pattern.size()-1; i+=6) {
        char bigLetter = pattern[i], smallLetter = pattern[i+1];
        inputDataCopy = data;

        auto endIter = remove_if(begin(inputDataCopy), end(inputDataCopy),[bigLetter, smallLetter](auto val){return val == bigLetter or val == smallLetter;});

        string_view reducedPolymer(inputDataCopy);
        unsigned endPos = endIter - begin(inputDataCopy);
        polymerSizes.emplace_back(getSolutionPart1(reducedPolymer.substr(0, endPos), pattern));
    }
    return *min_element(begin(polymerSizes), end(polymerSizes));
}


int main() {
    string inputData, patterns;
    createPatterns(patterns);
    loadData("input.txt", inputData);

    { // SOLUTION PART1
        Timer t;
        cout << getSolutionPart1(inputData, patterns) << endl;
    }

    { // SOLUTION PART2
        Timer t;
        cout << getSolutionPart2(inputData, patterns) << endl;
    }


    return 0;
}
