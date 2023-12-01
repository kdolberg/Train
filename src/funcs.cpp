#include <cctype>
#include <locale>
#include "funcs.h"

void print_compile_date() {
	std::cout << "Compiled " << __DATE__ << " " << __TIME__ << std::endl;
}

bool is_integer(const unsigned char * s) {
	for (int i = 0; s[i] != (unsigned char)'\0'; ++i) {
		if (!std::isdigit((s[i]))) {
			return false;
		}
	}
	return true;
}

bool num_args_is_incorrect(int _argc) {
	return _argc < EXPECTED_NUM_ARGS;
}

MachineLearning::scalar line(MachineLearning::scalar x) {
	return (a*x + b);
}

MachineLearning::TrainingDataset make_empty_dataset(MachineLearning::uint num_inputs, MachineLearning::uint num_outputs, MachineLearning::uint num_datapoints) {
	LinearAlgebra::Matrix x(MINDEX(num_inputs,num_datapoints)),y(MINDEX(num_outputs,num_datapoints));
	MachineLearning::TrainingDataset ret = {x,y};
	return ret;
}

MachineLearning::TrainingDataset make_linear_dataset() {
	MachineLearning::TrainingDataset ret = make_empty_dataset(1,1,NUM_DATAPOINTS);
	MachineLearning::scalar x = INIT_COND;
	for (MachineLearning::mindex i = {0,0}; i.col < NUM_DATAPOINTS; ++i.col) {
		ret.x[i] = x;
		ret.y[i] = line(x);
		x += INCREMENT;
	}
	return ret;
}

void print_args(int _argc, char const **_argv) {
	std::cerr << "PROGRAM ARGUMENTS:\t";
	for (int i = 0; i < _argc; ++i) {
		std::cerr << _argv[i] << " ";
	}
	std::cerr << std::endl;
}

#define SCALAR_TO_BOOL(__var__) (((__var__) >= 0.5f) ? true : false)

LinearAlgebra::Matrix XOR(LinearAlgebra::Matrix& m) {
	assert(m.get_num_rows()==2);
	assert(m.get_num_cols() > 0);
	LinearAlgebra::mindex_t dims = m.size();
	dims.row = 1;
	LinearAlgebra::Matrix ret(dims);

	for (LinearAlgebra::mindex_t i = {0,0}; i.col < m.get_num_cols(); ++i.col) {
		ret[i] = (1.0f)*(SCALAR_TO_BOOL(m[MINDEX(0,i.col)]) xor SCALAR_TO_BOOL(m[MINDEX(1,i.col)]));
	}
	return ret;
}

MachineLearning::TrainingDataset make_xor_dataset() {
	LinearAlgebra::Matrix _x = {{0,0},
								{0,1},
								{1,0},
								{1,1}};
	LinearAlgebra::Matrix x = LinearAlgebra::transpose(_x);
	MachineLearning::TrainingDataset ret = {x,XOR(x)};
	return ret;
}

std::string tolower(const char * str) {
	char tmp[strlen(str)+1];
	strcpy(tmp,str);
	std::locale loc;
	std::use_facet<std::ctype<char>>(loc).tolower(tmp,tmp+sizeof(tmp));
	return std::string(tmp);
}