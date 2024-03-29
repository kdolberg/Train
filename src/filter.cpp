#include "filter.h"

typedef la::scalar_t scalar;

Filter::Filter(la::uint N) {
	this->N = N;
	this->delay_line = std::list<scalar>();
}

scalar Filter::operator()(scalar x) {
		this->delay_line.push_back(x);

		while (this->delay_line.size() > this->N) {
			this->delay_line.pop_front();
		}

		scalar sum = 0;

		for (auto i = this->delay_line.cbegin(); i != this->delay_line.cend(); ++i) {
			sum += *i;
		}
		
		return sum/(1.0f*this->delay_line.size());
	}