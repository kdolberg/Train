#ifndef ARGUMENT_OPTIONS_H
#define ARGUMENT_OPTIONS_H

#include "machine_learning.h"

#define INPUT_NET			('n')
#define INPUT_TD			('t')
#define OUTPUT_NET			('o')
#define SET_LEARNING_RATE	('l')
#define MIN_ERROR			('m')
#define NUM_EPOCHS 			('e')
#define DYNAMIC_LR			('d')
#define META_LR				('q')
#define MIN_LEARNING_RATE	('r')
#define PRINT_INTERVAL		('p')

#define HELP 				('h')

#define COLON				(':')

#define ARG_OPTS {			INPUT_NET,COLON,\
							INPUT_TD,COLON,\
							OUTPUT_NET,COLON,\
							SET_LEARNING_RATE,COLON,\
							MIN_ERROR,COLON,\
							NUM_EPOCHS,COLON,\
							DYNAMIC_LR,COLON,\
							META_LR,COLON,\
							MIN_LEARNING_RATE,COLON,\
							PRINT_INTERVAL,COLON,\
							HELP}

#define MAX_FILENAME_LENGTH 255

typedef struct {
	ml::TrainingDataset td;
	ml::Net n;
	std::string output_net_filename = "outfile.nn";
	ml::scalar learning_rate = -1000.0f;
	ml::scalar min_error = 0.0f;
	ml::scalar min_learning_rate = 0.0f;
	ml::uint num_epochs = 100;
	bool dynamic_learning_rate = false;
	ml::uint filter_length = 0;
	ml::scalar meta_learning_rate = 0.1;
	bool learning_rate_user_defined = false;
	ml::uint print_interval = 10;
} ArgumentOptionOutputs;

ArgumentOptionOutputs parse_command_line_arguments(int argc, char * const argv[]);

#endif // ARGUMENT_OPTIONS_H