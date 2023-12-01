#include <math.h>
#include "main.h"

int main(int argc, char const *argv[]) {
	print_compile_date();

	if (argc==1) {
		std::cout << "No arguments received. Generating synthetic data.\n";
		MachineLearning::Net n_prev(MachineLearning::NetDef({2,2,1}),true);
		MachineLearning::save(n_prev,"outputs/forxor.nn");
		MachineLearning::save(make_linear_dataset(),"inputs/dataset.td");
		MachineLearning::save(make_xor_dataset(),"inputs/xor_dataset.td");
		return 0;
	}

	if (num_args_is_incorrect(argc)) {
		std::cerr << "Expected " << (EXPECTED_NUM_ARGS-1) << " arguments, but received " << (argc-1) << ".\nExiting.\n";
		return 1;
	}
	// PRINT_VAR(n_prev);
	
	MachineLearning::Net n;
	// MachineLearning::load(n,"prev.nn");
	// PRINT_VAR(n);
	// PRINT_VAR((n==n_prev));
	if(!MachineLearning::load(n,argv[NET_INDEX])) {
		std::cerr << "\"" << argv[NET_INDEX] << "\" is not a valid neural net file.\n";
		return 1;
	}

	std::cout << n.get_activation_function_list() << std::endl;

	MachineLearning::TrainingDataset td = make_linear_dataset();
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
			std::cout << "Iteration " << i << ": sqrt(2*E) = " << sqrt(2*n.learn(td)) << std::endl;
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

	if(argc >= PRINT_BOOL_INDEX) {
		if (tolower(argv[PRINT_BOOL_INDEX]) == std::string("true")) {
			MachineLearning::TrainingDataset test_results = {td.x, n(td.x)};
			std::cout << "Test results:\n";
			std::cout << test_results << std::endl;
		}
	} else {
		std::cout << "Closing\n";
	}
	return 0;
}