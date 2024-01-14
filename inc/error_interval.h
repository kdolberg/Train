#ifndef ERROR_INTERVAL_H

#include <sstream>

#include "interval.h"
#include "machine_learning.h"

class ErrorInterval : public Interval<ml::scalar> {
	ml::scalar * E;
public:
	ErrorInterval(ml::scalar * E) {
		this->E = E;
	}
	~ErrorInterval() {}
	
	ml::scalar update() {
		return *(this->E);
	}

	ml::scalar delta() const {
		return this->get_stop()-this->get_start();
	}

	std::string str() const {
		std::stringstream ss;
		ss << this->delta();
		return ss.str();
	}
};

#define ERROR_INTERVAL_H
#endif