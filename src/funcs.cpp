#include "funcs.h"

bool is_integer(const unsigned char * s) {
	for (int i = 0; s[i] != (unsigned char)'\0'; ++i) {
		if (!std::isdigit((s[i]))) {
			return false;
		}
	}
	return true;
}

bool num_args_is_incorrect(int _argc) {
	return _argc != EXPECTED_NUM_ARGS;
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