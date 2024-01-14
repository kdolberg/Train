#include <exception>
#include <iostream>
#include <unistd.h>
#include <assert.h>

#include "train_save_load.h"
#include "argument_options.h"

ArgumentOptionOutputs parse_command_line_arguments(int argc, char * const argv[]) {
	int opt = 0;

	char arg_opts[] = ARG_OPTS;

	ArgumentOptionOutputs ret;

	try {
		while ((opt = getopt(argc,argv,arg_opts)) != -1) {
			if (opt == INPUT_NET) {
				train::load(ret.n,optarg);
			} else if (opt == INPUT_TD) {
				train::load(ret.td,optarg);
			} else if (opt == OUTPUT_NET) {
				ret.output_net_filename.clear();
				ret.output_net_filename = std::string(optarg);
			} else if (opt == SET_LEARNING_RATE) {
				ret.learning_rate_user_defined = true;
				ret.learning_rate = std::stof(optarg);
			} else if (opt == MIN_ERROR) {
				ret.min_error = std::stof(optarg);
			} else if (opt == NUM_EPOCHS) {
				ret.num_epochs = std::stoi(optarg);
			} else if (opt == DYNAMIC_LR) {
				ret.dynamic_learning_rate = true;
				ret.filter_length = std::stoi(optarg);
			} else if (opt == META_LR) {
				ret.meta_learning_rate = std::stof(optarg);
			} else if (opt == MIN_LEARNING_RATE) {
				ret.min_learning_rate = std::stof(optarg);
			} else if (opt == PRINT_INTERVAL) {
				ret.print_interval = std::stof(optarg);
			} else if (opt == HELP) {
				std::cout << "Unfortunately, the help section hasn't been made yet. You're helpless.\n";
			} else {
				assert(false);
				std::cerr << "I don't know what, but something went wrong\n";
			}
			std::cout << (char)opt << " = " << optarg << std::endl;
		}
	} catch (std::exception& e) {
		std::cerr << "An error occured while parsing the argument options:\n";
		std::cerr << e.what();
	}
	return ret;
}