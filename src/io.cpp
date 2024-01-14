#include "io.h"

#define WIDTH 14
#define PRECISION 5
#define PRINT2(__var__,__str__)	std::cout << std::setw(WIDTH) << " " << __str__ << "=" 	<< std::setw(WIDTH) << std::setprecision(PRECISION) << __var__;
#define PRINT1(__var__)			PRINT2(__var__,#__var__);

void print_formatted_var(float num,int);