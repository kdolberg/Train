#include "main.h"

#define DEFAULT_LEARNING_RATE 0.1f

/**
 * @brief Returns true if all elements of the input character array (assumes null-terminated) are numeric digits
 */
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

#define a 0.5f
#define b 0.4f

MachineLearning::scalar line(MachineLearning::scalar x) {
	return (a*x + b);
}

MachineLearning::TrainingDataset make_empty_dataset(MachineLearning::uint num_inputs, MachineLearning::uint num_outputs, MachineLearning::uint num_datapoints) {
	LinearAlgebra::Matrix x(MINDEX(num_inputs,num_datapoints)),y(MINDEX(num_outputs,num_datapoints));
	MachineLearning::TrainingDataset ret = {x,y};
	return ret;
}

#define NUM_DATAPOINTS 100

MachineLearning::TrainingDataset make_linear_dataset() {
	MachineLearning::TrainingDataset ret = make_empty_dataset(1,1,NUM_DATAPOINTS);
	MachineLearning::scalar x = -200.0f;
	for (MachineLearning::mindex i = {0,0}; i.col < NUM_DATAPOINTS; ++i.col) {
		ret.x[i] = x;
		ret.y[i] = line(x);
		x += 2.0f;
	}
	return ret;
}

int main(int argc, char const *argv[]) {
	save(make_linear_dataset(),"linear_dataset.td");
	if (num_args_is_incorrect(argc)) {
		std::cerr << "Expected " << (EXPECTED_NUM_ARGS-1) << " arguments, but received " << (argc-1) << ".\nExiting.\n";
		return 1;
	}
	MachineLearning::Net n;
	if(!MachineLearning::load(n,argv[NET_INDEX])) {
		std::cerr << "\"" << argv[NET_INDEX] << "\" is not a valid neural net file.\n";
		return 1;
	}
	MachineLearning::TrainingDataset td;
	if(!MachineLearning::load(td,argv[DATASET_INDEX])) {
		std::cerr << "\"" << argv[DATASET_INDEX] << "\" is not a valid training dataset file.\n";
		return 1;
	}
	MachineLearning::uint num_epochs;
	if(is_integer((const unsigned char *)argv[NUM_ITERATIONS_INDEX])) {
		num_epochs = atoi(argv[NUM_ITERATIONS_INDEX]);
	} else {
		std::cerr << "\"" << argv[NUM_ITERATIONS_INDEX] << "\" is not an integer.\n";
		return 1;
	}
	MachineLearning::uint print_interval = num_epochs/10;
	for (MachineLearning::uint i = 0; i < num_epochs; ++i) {
		if((i % print_interval) == 0) {
			std::cout << "Iteration " << i << ": Error = " << n.learn(td) << std::endl;
		} else {
			n.learn(td);
		}
	}
	std::cout << "Training complete.\n";
	if(MachineLearning::save(n,argv[NET_OUTFILE_INDEX])) {
		std::cout << "Saved neural net as \"" << argv[NET_OUTFILE_INDEX] << "\".\n";
	} else {
		std::cerr << "Could not save neural net as \"" << argv[NET_OUTFILE_INDEX] << "\".\n";
		return 1;
	}
	return 0;
}