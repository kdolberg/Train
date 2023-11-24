#include "main.h"

int main(int argc, char const *argv[]) {
	MachineLearning::TrainingDataset td = make_linear_dataset();
	MachineLearning::Net n(MachineLearning::NetDef({1,1}));
	n.load_training_data(td);
	for (int i = 0; i < 100; ++i) {
		n.learn();
	}
	return 0;
}