#ifndef ARGUMENT_OPTIONS_H
#define ARGUMENT_OPTIONS_H

#define INPUT_NET			('n')
#define INPUT_TD			('t')
#define OUTPUT_NET			('o')
#define SET_LEARNING_RATE	('l')
#define MIN_ERROR			('m')
#define NUM_EPOCHS 			('e')
#define DYNAMIC_LR			('d')
#define META_LR				('q')

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
							HELP}

#define MAX_FILENAME_LENGTH 255

// #define LONG_INPUT_NET			"innet"
// #define LONG_INPUT_TD			"td"
// #define LONG_OUTPUT_NET			"outnet"
// #define LONG_SET_LEARNING_RATE  "learnrate"
// #define LONG_MIN_ERROR			"minerror"
// #define LONG_HELP				"help"
// #define LONG_NUM_EPOCHS			"epochs"

#endif // ARGUMENT_OPTIONS_H