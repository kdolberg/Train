# Linear algebra objects
LA_DIR = ../../LinearAlgebra
LA_OBJ = la_basic_types.la la_matrix.la la_matrix_like.la la_vector.la la_vector_overloads.la
LA_OBJ_FULL_PATH = $(patsubst la_%.la, $(LA_DIR)/obj/la_%.la, $(LA_OBJ))

# MachineLearning objects
ML_DIR = ../../MachineLearning
ML_OBJ = activation_function.ml layer.ml net.ml save_load.ml
ML_OBJ_FULL_PATH = $(patsubst %.ml, $(ML_DIR)/obj/%.ml, $(ML_OBJ))

# Train objects
TRAIN_OBJ = main.o
TRAIN_OBJ_FULL_PATH = $(patsubst %.o, obj/%.o, $(TRAIN_OBJ))
TARGET = bin/mklineartd

# Comprehensive list of all objects needed to build the target
ALL_OBJ = $(TRAIN_OBJ_FULL_PATH) $(ML_OBJ_FULL_PATH) $(LA_OBJ_FULL_PATH)

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -g -O2 -MMD -MP

# Includes
INCLUDES = -I. -I./inc -I./$(ML_DIR) -I./$(ML_DIR)/inc -I./$(LA_DIR) -I./../../confirm/inc -I./../../confirm -I./$(LA_DIR)/include

# Rule for target
$(TARGET): $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ALL_OBJ) -o $(TARGET)

obj/%.o: src/%.cpp inc/%.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(LA_DIR)/obj/la_%.la:
	$(MAKE) la

la:
	$(MAKE) -C $(LA_DIR) $(patsubst la_%.la, obj/la_%.la, $(LA_OBJ)) CXXFLAGS="$(CXXFLAGS)"

$(ML_DIR)/obj/%.ml:
	$(MAKE) ml

ml:
	$(MAKE) -C $(ML_DIR) $(patsubst %.ml, obj/%.ml, $(ML_OBJ))

# By default, only clean the objects from this project
clean:
	rm -f $(TRAIN_OBJ) $(TARGET)

clean_la:
	rm -f $(LA_OBJ_FULL_PATH)

clean_ml:
	rm -f $(ML_OBJ_FULL_PATH)

clean_all:
	$(MAKE) clean
	$(MAKE) clean_la
	$(MAKE) clean_ml

all: $(TARGET)

run: $(TARGET)
	./$(TARGET).exe

debug: $(TARGET)
	gdb $(TARGET).exe

.PHONY: clean run all clean_la la ml clean_ml debug