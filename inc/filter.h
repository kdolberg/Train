#ifndef FILTER_H
#define FILTER_H

#include <list>
#include "linear_algebra.h"

class Filter {
	LinearAlgebra::uint N;
	std::list<LinearAlgebra::scalar_t> delay_line;
public:
	Filter(LinearAlgebra::uint);
	LinearAlgebra::scalar_t operator()(LinearAlgebra::scalar_t);
};

#endif // FILTER_H