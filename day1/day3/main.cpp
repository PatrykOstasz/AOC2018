#include <algorithm>
#include <cctype>
#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Timer.h"

using namespace std;

struct ElfClaim {
    unsigned id;
    unsigned leftOffset;
    unsigned topOffset;
    unsigned width;
    unsigned height;
};

void loadData(vector<ElfClaim>& data);
ElfClaim parseData(string& line);
pair<unsigned, unsigned> findMaxClothDimensions(const vector<ElfClaim>& data);
vector<vector<int>> createCloth(unsigned width, unsigned height);
unsigned countSquareInches(const vector<ElfClaim>& claims, vector<vector<int>>& cloth);
unsigned insertClaim(const ElfClaim& claim, vector<vector<int>>& cloth);
unsigned findBestClaim(const vector<ElfClaim>& claims, const vector<vector<int>>& cloth);


int main()
{
    const unsigned dataCount = 1323;
    vector<ElfClaim> inputData;
    inputData.reserve(dataCount);

    loadData(inputData);
    auto[maxWidth, maxHeight] = findMaxClothDimensions(inputData);
    vector<vector<int>> cloth = createCloth(maxWidth, maxHeight);

    cout << "Day3, part1 = " << countSquareInches(inputData, cloth) << endl;
    cout << "Day3, part2 = " << findBestClaim(inputData, cloth) << endl;
}


void loadData(vector<ElfClaim>& data) {
    ifstream file("input.txt");
    string line;
    while (!file.eof()) {
        getline(file, line);
        data.emplace_back(parseData(line));
    }
    file.close();
}

ElfClaim parseData(string& line) {
    line.erase(remove(begin(line), end(line), ' '), end(line));
    ElfClaim claim;
    unsigned* ptr = reinterpret_cast<unsigned*>(&claim);

    string_view iv(line);
    auto delim_begin = begin(iv);
    while(true) {
        auto delim_end = find_if(delim_begin+1, end(iv), [](auto ch){return !isdigit(ch);});

        auto delim_start_pos = delim_begin + 1 - begin(iv);
        auto delim_end_pos = delim_end - begin(iv);

        auto item_substr = iv.substr(delim_start_pos, delim_end_pos);
        from_chars(item_substr.data(), item_substr.data() + item_substr.size(), *ptr);

        ptr++;
        if (delim_end == end(iv)) break;
        delim_begin = delim_end;
    }
    return claim;
}

pair<unsigned, unsigned> findMaxClothDimensions(const vector<ElfClaim>& data) {
    vector<unsigned> rectWidths, rectHeights;
    rectWidths.reserve(1323);
    rectHeights.reserve(1323);

    for (const auto& item : data) {
        rectHeights.emplace_back(item.topOffset + item.height);
        rectWidths.emplace_back(item.leftOffset + item.width);
    }
    unsigned maxWidth = *max_element(begin(rectWidths), end(rectWidths));
    unsigned maxHeight = *max_element(begin(rectHeights), end(rectHeights));
    return make_pair(maxWidth, maxHeight);
}

vector<vector<int>> createCloth(unsigned width, unsigned height) {
    vector<vector<int>> cloth(width, vector<int>(height, 0));
    return cloth;
}

unsigned countSquareInches(const vector<ElfClaim>& claims, vector<vector<int>>& cloth) {
    unsigned squareInchCount = 0;
    for (const auto& c : claims) {
        squareInchCount+=insertClaim(c, cloth);
    }
    return squareInchCount;
}

unsigned insertClaim(const ElfClaim& claim, vector<vector<int>>& cloth) {
    unsigned squareInches = 0;
    auto[id, lOff, tOff, w, h] = claim;
    for (unsigned i = lOff; i < lOff+w; ++i) {
        for(unsigned j = tOff; j < tOff+h; ++j) {
            if (cloth[i][j] == -1) continue;
            if (cloth[i][j] > 0) {
                squareInches++;
                cloth[i][j] = -1;
            } else {
                cloth[i][j] = id;
            }
        }
    }
    return squareInches;
}

unsigned findBestClaim(const vector<ElfClaim>& claims, const vector<vector<int>>& cloth) {
    vector<unsigned> expectedSquareInches;
    expectedSquareInches.reserve(claims.size());
    vector<unsigned> actualSquareInches(claims.size(), 0);
    for (const auto& claim : claims) {
        expectedSquareInches.emplace_back(claim.width*claim.height);
    }

    for (const auto& iElem : cloth) {
        for (const auto& jElem : iElem) {
            if (jElem == -1 or jElem == 0) continue;
            actualSquareInches[jElem-1]++;
        }
    }
    for (unsigned i = 0; i < expectedSquareInches.size(); ++i) {
        if (expectedSquareInches[i] == actualSquareInches[i])
            return i+1;
    }

    return 0;
}

