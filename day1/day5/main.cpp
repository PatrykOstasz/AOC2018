#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;

unsigned findMatch(unsigned lb, unsigned ub, const string& pattern, const string& data, unsigned& counter) {
    cout << "Dafaq " << lb << " " << ub << " " << pattern << " " << counter << endl;
    if ((data[lb] == pattern[0] and data[ub] == pattern[1]) or (data[lb] == pattern[1] and data[ub] == pattern[0])) {
        counter+=2;
        findMatch(lb-1, ub+1, pattern, data, counter);
    }
    return ub;
}

int main()
{
    string inputData("");
    string regexData;
    stringstream ss;

    unsigned asciiLetterOffset = 32;
    for (char i = 'A'; i <= 'Z'; ++i)
        ss << i << char(i+asciiLetterOffset);
    regexData = ss.str();
    ifstream file("input.txt");
    file >> inputData;
    file.close();
    unsigned counter {};
    for (int i = 0; i < regexData.size(); i+=2){
        string lookUp = regexData.substr(i, i+2);
        unsigned indexStart = 0;
        while(indexStart < inputData.size()) {
            auto iBegin = inputData.find(lookUp, indexStart);
            if (iBegin != string::npos){
                counter+=2;
                indexStart = findMatch(iBegin-1, iBegin+2, lookUp, inputData, counter);
                cout << indexStart << endl;
            }
        }
    }
    cout << counter << endl;
    return 0;
}
