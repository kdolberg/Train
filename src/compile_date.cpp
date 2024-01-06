#include "compile_date.h"

std::string compile_date() {
	std::string ret(__DATE__);
	ret += " ";
	ret += __TIME__;
	return ret;
}