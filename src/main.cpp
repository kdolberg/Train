#include <math.h>
#include "main.h"

#include <chrono>
#include <iostream>
#include <sstream>

#define MEASURE_DURATION(CMD) tick();CMD;tock();get_stream()<<#CMD<<":\t";to_stream();

#define MIN_LEARNING_RATE 1e-8

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
	int load(T& t, const char * filename) {
		auto ret = MachineLearning::load(t,filename);
		if (ret) {
			std::cout << filename << " loaded successfully.\n";
		} else {
			std::invalid_argument e(std::string(filename) + " could not be loaded.\n");
			throw e;
		}
		return ret;
	}

	template <typename T>
	int save(const T& t, const char * filename) {
		auto ret = MachineLearning::save(t,filename);
		if (ret) {
			// std::cout << filename << " saved successfully.\n";
		} else {
			std::invalid_argument e(std::string(filename) + " could not be saved.\n");
			throw e;
		}
		return ret;
	}
}

int main(int argc, char * const argv[]) {
	print_compile_date();

	// This is where we start our refactor
	int opt = 0;

	char arg_opts[] = ARG_OPTS;

	MachineLearning::TrainingDataset td;
	MachineLearning::Net n;
	std::string output_net_filename = "outfile.nn";
	MachineLearning::scalar learning_rate = -1;
	MachineLearning::scalar min_error = 0.0f;
	MachineLearning::uint num_epochs = 100;
	bool dynamic_learning_rate = false;
	MachineLearning::uint filter_length = 0;
	MachineLearning::scalar meta_learning_rate = 0;
	try {
		while ((opt = getopt(argc,argv,arg_opts)) != -1) {
			if (opt == INPUT_NET) {
				train::load(n,optarg);
			}else if (opt == INPUT_TD) {
				train::load(td,optarg);
			}else if (opt == OUTPUT_NET) {
				output_net_filename.clear();
				output_net_filename = std::string(optarg);
			}else if (opt == SET_LEARNING_RATE) {
				learning_rate = std::stof(optarg);
			}else if (opt == MIN_ERROR) {
				min_error = std::stof(optarg);
			}else if (opt == NUM_EPOCHS) {
				num_epochs = std::stoi(optarg);
			}else if (opt == DYNAMIC_LR) {
				dynamic_learning_rate = true;
				filter_length = std::stoi(optarg);
			} else if (opt == META_LR) {
				meta_learning_rate = std::stof(optarg);
			}else if (opt == HELP) {
				std::cout << "Unfortunately, the help section hasn't been made yet. You're helpless.\n";
				return 0;
			}else {
				assert(false);
				std::cerr << "I don't know what, but something went wrong\n";
				return -1;
			}
			std::cout << (char)opt << " = " << optarg << std::endl;
		}

		MachineLearning::scalar Erms = 1+min_error, E;
		MachineLearning::uint print_interval = num_epochs/10;

		if (learning_rate > 0) {
			n.learning_rate = learning_rate;
			std::cout << "The learning rate has been changed by the user. This change will be saved in the neural net file.\n";
		} else {
			learning_rate = n.learning_rate;
		}
		std::cout << "The learning rate is " << n.learning_rate << ".\n";
		n.load_training_data(td);

		Filter f1(filter_length),f2(filter_length);
		MachineLearning::scalar Eavg1=0,Eavg2=0,h=1e-5;

		tick();
		for (MachineLearning::uint i = 0; (i < num_epochs) && (Erms > min_error); ++i) {
			n.learning_rate = (dynamic_learning_rate && !(i%2)) ? learning_rate : learning_rate+h;
			E = n.learn();

			if(dynamic_learning_rate) {
				if (!(i%2)) {
					Eavg1 = f1(E);
				} else {
					Eavg2 = f2(E);
					learning_rate += (i > filter_length) ? meta_learning_rate*(Eavg2-Eavg1)/h : 0.0f;
					if (learning_rate < MIN_LEARNING_RATE) {
						learning_rate = MIN_LEARNING_RATE;
					}
				}
			}

			if((i % print_interval) == 0) {
				Erms = sqrt(2*E);
				std::cout << "Iteration " << i << ":\tErms = " << Erms << "\tlr = " << learning_rate << "\tDuration = " << tock() << std::endl;
				train::save(n,output_net_filename.c_str());
			}
		}
		std::cout << "Training complete.\n";
		if(train::save(n,output_net_filename.c_str())) {
			std::cout << "Saved neural net as \"" << output_net_filename.c_str() << "\".\n";
		} else {
			std::cerr << "Could not save neural net as \"" << output_net_filename.c_str() << "\".\n";
			return 1;
		}
	} catch (std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
		return -1;
	}
	return 0;
}