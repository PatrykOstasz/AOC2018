#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <charconv>
#include <tuple>
#include <map>

#include "../common.h"

using GuardShiftMap = unordered_multimap<unsigned, tuple<unsigned, unsigned, unsigned>>;

bool checkField(unsigned& field, const std::string& item, const std::string& pattern, char begin, char end) {
    if (item.find(pattern) != string::npos) {
        size_t guardIdBegin = item.find(begin);
        size_t guardIdEnd = item.find(end, guardIdBegin);
        from_chars(item.data()+ guardIdBegin+1, item.data() + guardIdEnd, field);
        return true;
    }
    return false;
}

GuardShiftMap createGuardShiftShedule(const vector<string>& data) {
    GuardShiftMap guardShiftMap;
    unsigned guardId = 0, fallsAsleep = 0, wakesUp = 0;
    for (const auto& item : data) {
        if (checkField(guardId, item, "begins shift", '#', ' ')) continue;
        if (checkField(fallsAsleep, item, "falls asleep", ':', ']')) continue;
        checkField(wakesUp,item, "wakes up", ':', ']');
        guardShiftMap.insert(make_pair(guardId, make_tuple(wakesUp, fallsAsleep, wakesUp-fallsAsleep)));
    }
    return guardShiftMap;
}

unsigned findGuardId(const GuardShiftMap& schedule) {
    unordered_map<unsigned, unsigned> sleepDuration;
    for (auto[k,v] : schedule) {
        sleepDuration[k] += get<2>(v);
    }
    auto maxSched = *max_element(begin(sleepDuration), end(sleepDuration), [](auto v1, auto v2){return v2.second > v1.second;});
    return maxSched.first;
}

unsigned findMinuteSleptForFoundGuard(unsigned guardId, const GuardShiftMap& schedule) {
    unordered_multiset<unsigned> minutesSlept {};
    for (auto[k,v] : schedule) {
        if (k == guardId) {
            auto[wu, fa, m] = v;
            for (unsigned i = fa; i < wu; ++i)
                minutesSlept.insert(i);
        }
    }
    auto pred = [minutesSlept](auto v1, auto v2){return minutesSlept.count(v2) > minutesSlept.count(v1);};
    return *max_element(begin(minutesSlept), end(minutesSlept), pred);
}

pair<unsigned,unsigned> findGuardMostFrequentlySleeping(const GuardShiftMap& schedule) {
    map<pair<unsigned, unsigned>, unsigned> sleepDuration;
    for (auto[k,v] : schedule) {
        auto[wu, fa, m] = v;
        for (unsigned i = fa; i < wu; ++i){
            sleepDuration.insert(make_pair(make_pair(k,i),0));
            sleepDuration.find({k,i})->second++;
        }
    }
    auto pred = [sleepDuration](auto v1, auto v2){return  v2.second > v1.second;};
    auto result = *max_element(begin(sleepDuration), end(sleepDuration), pred);
    return {result.first.first, result.first.second};
}

int main(){
    const string filename = "input.txt";
    vector<string> inputData;
    inputData.reserve(countLines(filename));
    loadData(filename, inputData, true);
    printData(inputData);
    GuardShiftMap schedule = createGuardShiftShedule(inputData);
    { //SOLUTION PART1
        Timer t;
        unsigned foundGuard = findGuardId(schedule);
        unsigned minutesSlept = findMinuteSleptForFoundGuard(foundGuard, schedule);
        cout << foundGuard << " " << minutesSlept << " " << foundGuard*minutesSlept << endl;
    }
    { //SOLUTION PART2
        Timer t;
        auto[guardId, mostFrequentMinute] = findGuardMostFrequentlySleeping(schedule);
        cout << guardId << " " << mostFrequentMinute << " " << guardId*mostFrequentMinute << endl;
    }
    return 0;
}
