#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>
#include <unordered_set>

#include "Timer.h"

using namespace std;

struct Solution {
    int sol1 = 0;
    int sol2 = 0;
};

unsigned count_frequencies(ifstream& file);
int find_duplicates(int freq);
Solution solution(const std::string& name);

int main()
{
    string filename = "input.txt";
    auto[res1, res2] = solution(filename);
    cout << "Freq sum = " << res1 << endl;
    cout << "first duplicate = " << res2 << endl;

    return 0;
}

unsigned count_frequencies(ifstream& file) {
    unsigned result = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
    file.clear();
    file.seekg(0);
    return result;
}

int find_duplicates(const vector<int>& freqs) {
    Timer timer;
    int sum = 0;
    unordered_set<int> duplicates;
    duplicates.emplace(0);
    while (true) {
        for (auto f : freqs) {
            sum += f;
            if (duplicates.count(sum) == 0) {
                duplicates.emplace(sum);
            } else {
                return sum;
            }
        }
    }
}

Solution solution(const std::string& name) {
    Timer t;
    ifstream file(name);
    vector<int> frequencies;
    frequencies.reserve(count_frequencies(file));

    string temp;
    while (!file.eof()) {
        file >> temp;
        frequencies.emplace_back(stoi(temp));
    }

    int freq_sum = accumulate(begin(frequencies), end(frequencies), 0);
    int duplicate = find_duplicates(frequencies);
    return {freq_sum, duplicate};
}
