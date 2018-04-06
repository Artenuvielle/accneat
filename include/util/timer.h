#pragma once
#include <chrono>

namespace NEAT {
    class Timer {
        static std::vector<Timer *> timers;

        const char *_name;
        size_t _n = 0;
        double _total = 0.0;
        double _min = 0.0;
        double _max = 0.0;
		std::chrono::time_point<std::chrono::system_clock> _start;
		bool _started = false;
        double _recent = 0.0;
    public:
        Timer(const char *name);
        ~Timer();
    
        void start();
        void stop();

        static void report();
    };
}
