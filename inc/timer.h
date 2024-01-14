#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <sstream>
#include "interval.h"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;

class Timer : public Interval<time_point> {
public:
	Timer() {
		this->_start = std::chrono::high_resolution_clock::now();
		this->_stop = std::chrono::high_resolution_clock::now();
	}
	~Timer() {}

	time_point update() {
		return std::chrono::high_resolution_clock::now();
	}

	std::string str() const {
		std::stringstream ss;
		ss << std::chrono::duration_cast<std::chrono::nanoseconds>(this->get_stop() - this->get_start()).count()*(1e-9);
		ss << " seconds";
		return ss.str();
	}

	float delta() const {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(this->get_stop() - this->get_start()).count()*(1e-9);
	}
};

#endif // TIMER_H