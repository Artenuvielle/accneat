#include "util/std.h" // Must be included first. Precompiled header with standard library includes.
#include "util/timer.h"
#include <assert.h>

using namespace NEAT;
using namespace std;

vector<Timer *> Timer::timers;

Timer::Timer(const char *name) : _name(name) {
    timers.push_back(this);
}

Timer::~Timer() {
    timers.erase(find(timers.begin(), timers.end(), this));
}

void Timer::start() {
    assert(_started == false);
    _start = std::chrono::system_clock::now();
	_started = true;
}

void Timer::stop() {
    assert(_started == true);

    double t = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _start).count();
    _recent = t;
	_started = false;

    if(_n == 0) {
        _min = _max = t;
    } else {
        _min = min(_min, t);
        _max = max(_max, t);
    }
    _total += t;
    _n++;
}

void Timer::report() {
    for(Timer *t: timers) {
        cout << t->_name << ": n=" << t->_n << ", recent=" << t->_recent << ", mean=" << (t->_total / t->_n) << ", min=" << t->_min << ", max=" << t->_max << ", total=" << t->_total << endl;
    }
}
