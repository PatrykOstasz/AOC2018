#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <sstream>

#include "../common.h"

using namespace std;

int main(){
    const string filename = "input.txt";
    vector<string> inputData;
    inputData.reserve(countLines(filename));
    loadData(filename,inputData, false);
    //printData(inputData);

    //This could be not optimal due to string
    set<pair<int, int>> locations;
    for (const auto& item : inputData) {
        auto delim = item.find(',');
        int x = stoi(item.substr(0, delim+1));
        int y = stoi(item.substr(delim+2, item.size()-(delim+2)));
        locations.insert(make_pair(x, y));
    }

    auto maxCoordX = *max_element(begin(locations), end(locations),[](auto p1, auto p2){return p2.first > p1.first;});
    auto maxCoordY = *max_element(begin(locations), end(locations),[](auto p1, auto p2){return p2.second > p1.second;});
    unsigned mapSize = max(maxCoordX.first, maxCoordY.second) + 1; // this is not needed cause not every dimension is similar in size
    map<pair<int, int>, pair<char, int>> coordsToDistance;
    char index = 'a';
    char bigIndex = 'A';
    // This is not optimal by using map (if the dimensions are like couple of hundred it will slow down on insert due to map sorting each key
    // Additionally there is too much locations that could be represented as letters.
    for (const auto& loc : locations) {
        auto[x,y] = loc;
        int xCoord {}, yCoord {};
        while (xCoord <= mapSize and yCoord <= mapSize) {
            auto manhattan_distance = abs(x - xCoord) + abs(y - yCoord);
            if (xCoord == x and yCoord == y) {
                coordsToDistance[{xCoord, yCoord}] = make_pair(bigIndex, 0);
            } else {
                if (coordsToDistance.count({xCoord, yCoord}) == 1) {
                    if (coordsToDistance[{xCoord, yCoord}].second > manhattan_distance) {
                        coordsToDistance[{xCoord, yCoord}] = make_pair(index, manhattan_distance);

                    } else if (coordsToDistance[{xCoord, yCoord}].second == manhattan_distance) {
                        coordsToDistance[{xCoord, yCoord}] = make_pair('.', manhattan_distance);

                    }
                } else {
                    coordsToDistance[{xCoord, yCoord}] = make_pair(index, manhattan_distance);
                }
            }
            if (yCoord == mapSize)  {
                yCoord = 0;
                xCoord++;
                continue;
            }
            yCoord++;
        }
        index++;
        bigIndex++;
    }
    /*for (int i = 0; i < mapSize; ++i) {
        for (int j = 0; j < mapSize; ++j){
            cout << coordsToDistance[{j, i}].first << " ";
        }
        cout << endl;
    }*/
    unsigned maxVal = 0;
    for (char c = 'a'; c <= c+locations.size(); c++) {
        int xCoord {}, yCoord {};
        unsigned sum = 0;
        auto top    = coordsToDistance[{0, 0}].first;
        auto left   = coordsToDistance[{mapSize, 0}].first;
        auto right  = coordsToDistance[{0, mapSize}].first;
        auto bottom = coordsToDistance[{mapSize, mapSize}].first;
        if (c == top or c == left or c == right or c == bottom) continue;
        while (xCoord <= mapSize and yCoord <= mapSize) {
            if (coordsToDistance[{xCoord, yCoord}].first == c) sum++;
            if (yCoord == mapSize)  {
                yCoord = 0;
                xCoord++;
                continue;
            }
            yCoord++;
        }
        if (sum > maxVal) maxVal = sum;
    }
    cout << maxVal + 1 << endl;
    return 0;
}
