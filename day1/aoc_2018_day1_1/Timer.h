#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <chrono>

using namespace std::chrono;
using std::cout;
using std::endl;

class Timer {
public:
    using clock = high_resolution_clock;

    Timer() {
        startPoint = clock::now();
    }

    ~Timer() {
        stop();
    }

    void stop() {
        auto endPoint = clock::now();

        auto startp = time_point_cast<microseconds>(startPoint);
        auto endp = time_point_cast<microseconds>(endPoint);

        auto startpcount = startp.time_since_epoch().count();
        auto endpcount = endp.time_since_epoch().count();

        auto duration = endpcount - startpcount;
        double ms = duration*0.001;

        cout << "in microseconds: " << duration << "us" << endl;
        cout << "in miliseconds:  " << ms << "ms" << endl;
        cout << endl;
    }
private:
    time_point<clock> startPoint;
};


#endif // TIMER_H_INCLUDED
