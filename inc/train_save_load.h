#ifndef TRAIN_SAVE_LOAD_H
#define TRAIN_SAVE_LOAD_H

#include <exception>

#include "machine_learning.h"

namespace train {
	template <typename T>
	int load(T& t, const char * filename) {
		auto ret = ml::load(t,filename);
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
		auto ret = ml::save(t,filename);
		if (ret) {
			// std::cout << filename << " saved successfully.\n";
		} else {
			std::invalid_argument e(std::string(filename) + " could not be saved.\n");
			throw e;
		}
		return ret;
	}
}

#endif // TRAIN_SAVE_LOAD_H