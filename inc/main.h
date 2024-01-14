#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <exception>
#include <cstring>
#include <math.h>
#include <chrono>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "train_save_load.h"
#include "funcs.h"
#include "argument_options.h"
#include "filter.h"
#include "timer.h"
#include "error_interval.h"

#define WIDTH_WITHIN  10
#define WIDTH_BETWEEN 10
#define PRECISION 6
#define PRINT2(__var__,__str__)	std::cout << std::setw(WIDTH_BETWEEN) << " " << __str__ << " = " 	<< std::setw(WIDTH_WITHIN) << std::setprecision(PRECISION) << std::scientific << __var__;
#define PRINT1(__var__)			PRINT2(__var__,#__var__);

#endif // MAIN_H