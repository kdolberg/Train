#include "main.h"

#define a 0.5f
#define b 0.4f
#define NUM_DATAPOINTS 100
#define DEFAULT_FILENAME "linear_dataset.td"

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
	MachineLearning::scalar x = -200.0f;
	for (MachineLearning::mindex i = {0,0}; i.col < NUM_DATAPOINTS; ++i.col) {
		ret.x[i] = x;
		ret.y[i] = line(x);
		x += 2.0f;
	}
	return ret;
}

int main(int argc, char const *argv[]) {
	if(save(make_linear_dataset(),DEFAULT_FILENAME)) {
		std::cout << "Saved \"" << DEFAULT_FILENAME << "\".\n";
	} else {
		std::cerr << "Could not save \"" << DEFAULT_FILENAME << "\".\n";
	}
}