#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stack>

using namespace std;


unsigned findMatch(unsigned lb, unsigned ub, const string& patterns, const string& data, stack<unsigned>& unitIndices) {
    static unsigned levelOfSearch = 0;
    char searchPair[] = {data[lb], data[ub], '\0'};
    string searchString(searchPair);
    //cout << "[" << lb << ":" << ub << "] " << searchString << "\n";
    if ((patterns.find(searchString) != string::npos)) {
        if (levelOfSearch == 0 or ub == data.size()-1) return ub +1;
        lb = unitIndices.top();
        unitIndices.pop();
        levelOfSearch--;
        return findMatch(lb, ub+1, patterns, data, unitIndices);

    }
    levelOfSearch++;
    unitIndices.push(lb);
    return ub;
}

int main()
{
    string inputData("");
    string patterns;
    stringstream ss;

    unsigned asciiLetterOffset = 32;
    for (char i = 'A'; i <= 'Z'; ++i){
        ss << i << char(i+asciiLetterOffset) << " " << char(i+asciiLetterOffset) << i<<" ";
    }
    patterns = ss.str();
    ifstream file("input.txt");
    file >> inputData;
    file.close();
    stack<unsigned> polymerUnitsIndices;
    polymerUnitsIndices.push(0);
    unsigned indexStart = 0;
    while(indexStart < inputData.size()-1) {
        unsigned iBegin = indexStart;
        indexStart = findMatch(iBegin, iBegin+1, patterns, inputData, polymerUnitsIndices);
    }
    cout << polymerUnitsIndices.size() << endl;
    return 0;
}
