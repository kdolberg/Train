#include <math.h>
#include "main.h"

#include <chrono>
#include <iostream>
#include <sstream>

#define MEASURE_DURATION(CMD) tick();CMD;tock();get_stream()<<#CMD<<":\t";to_stream();

static auto start = std::chrono::high_resolution_clock::now();
static auto end = std::chrono::high_resolution_clock::now();
// static std::stringstream ss;

/**
 * Starts the stop watch
 */
void tick(){
	start = std::chrono::high_resolution_clock::now();
}

/**
 * Stops the stop watch
 */
std::string tock(){
	end = std::chrono::high_resolution_clock::now();
	std::stringstream ss;
	ss << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()*(1e-9)) << " seconds";
	tick();
	return ss.str();
}

namespace train {
	template <typename T>
	int load(const T& t, const char * filename) {
		if (strlen(filename) <= MAX_FILENAME_LENGTH) {
			return MachineLearning::load(t,filename);
		} else {
			std::invalid_argument e("The filename \"" + std::string(filename) + "\" is too long.\n");
			throw e;
			return 0;
		}
	}

	template <typename T>
	int save(const T& t, const char * filename) {
		if (strlen(filename) <= MAX_FILENAME_LENGTH) {
			return MachineLearning::save(t,filename);
		} else {
			std::invalid_argument e("The filename \"" + std::string(filename) + "\" is too long.\n");
			throw e;
			return 0;
		}
	}
}

int main(int argc, char * const argv[]) {
	print_compile_date();

	// if (argc==1) {
	// 	std::cout << "No arguments received. Generating synthetic data.\n";
	// 	MachineLearning::Net n_prev(MachineLearning::NetDef({2,2,1}),true);
	// 	MachineLearning::save(n_prev,"outputs/forxor.nn");
	// 	MachineLearning::save(make_linear_dataset(),"inputs/dataset.td");
	// 	MachineLearning::save(make_xor_dataset(),"inputs/xor_dataset.td");
	// 	return 0;
	// }

	// This is where we start our refactor
	int opt = 0;

	char arg_opts[] = ARG_OPTS;

	MachineLearning::TrainingDataset td;
	MachineLearning::Net n;
	char output_net_filename[MAX_FILENAME_LENGTH];

	try {
		while ((opt = getopt(argc,argv,arg_opts)) != -1) {
			if (opt == INPUT_NET ) {

			}else if (opt == INPUT_TD) {
				MachineLearning::load(td,optarg);
			}else if (opt == OUTPUT_NET) {
				strcpy(output_net_filename,optarg);
			}else if (opt == SET_LEARNING_RATE) {

			}else if (opt == MIN_ERROR) {

			}else if (opt == NUM_EPOCHS) {

			}else if (opt == HELP) {

			}else {
				assert(false);
				std::cerr << "I don't know what, but something went wrong\n";
				return -1;
			}
			std::cout << (char)opt << " = " << optarg << std::endl;
		}
	} catch (std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return -1;
	}

	/*DON'T CHANGE ANY OF THE STUFF BELOW JUST YET!*/

	// MachineLearning::scalar min_error = 0.1f;
	// MachineLearning::scalar Erms = 1+min_error;
	// MachineLearning::uint print_interval = num_epochs/10;
	// tick();
	// for (MachineLearning::uint i = 0; (i < num_epochs) && (Erms > min_error); ++i) {
	// 	if((i % print_interval) == 0) {
	// 		Erms = sqrt(2*n.learn(td));
	// 		std::cout << "Iteration " << i << ":\tErms = " << Erms << "\tDuration = " << tock() << std::endl;
	// 		if(MachineLearning::save(n,argv[NET_OUTFILE_INDEX])) {
	// 			std::cout << "Saved neural net as \"" << argv[NET_OUTFILE_INDEX] << "\".\n";
	// 		} else {
	// 			std::cerr << "Could not save neural net as \"" << argv[NET_OUTFILE_INDEX] << "\".\n";
	// 			return 1;
	// 		}
	// 	} else {
	// 		n.learn(td);
	// 	}
	// }
	// std::cout << "Training complete.\n";
	// if(MachineLearning::save(n,argv[NET_OUTFILE_INDEX])) {
	// 	std::cout << "Saved neural net as \"" << argv[NET_OUTFILE_INDEX] << "\".\n";
	// } else {
	// 	std::cerr << "Could not save neural net as \"" << argv[NET_OUTFILE_INDEX] << "\".\n";
	// 	return 1;
	// }

	// if(argc >= PRINT_BOOL_INDEX) {
	// 	if (tolower(argv[PRINT_BOOL_INDEX]) == std::string("true")) {
	// 		MachineLearning::TrainingDataset test_results = {td.x, n(td.x)};
	// 		std::cout << "Test results:\n";
	// 		std::cout << test_results << std::endl;
	// 	}
	// } else {
	// 	std::cout << "Closing\n";
	// }
	return 0;
}