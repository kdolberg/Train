#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>

#include "machine_learning.h"
#include "linear_algebra.h"
#include "UnitTest.h"

#define DEFAULT_LEARNING_RATE	(0.1f)
#define a						(0.5f)
#define b						(0.4f)
#define NUM_DATAPOINTS			(20)
#define INIT_COND				(0.0f)
#define INCREMENT				((1.0f)/NUM_DATAPOINTS)

#define NET_INDEX				(1)
#define DATASET_INDEX			(2)
#define NET_OUTFILE_INDEX		(3)
#define NUM_ITERATIONS_INDEX	(4)
#define EXPECTED_NUM_ARGS		(5)

/**
 * @brief Returns true if all elements of the input character array (assumes null-terminated) are numeric digits
 */
bool is_integer(const unsigned char * s);

bool num_args_is_incorrect(int _argc);

MachineLearning::scalar line(MachineLearning::scalar x);

MachineLearning::TrainingDataset make_empty_dataset(MachineLearning::uint num_inputs, MachineLearning::uint num_outputs, MachineLearning::uint num_datapoints);

MachineLearning::TrainingDataset make_linear_dataset();

void print_args(int _argc, char const **_argv);

#endif // FUNCS_H