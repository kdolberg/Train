# MachineLearning objects
ML_DIR = ./MachineLearning
ML_OBJ = activation_function.ml layer.ml net.ml save_load.ml types.ml
ML_OBJ_FULL_PATH = $(patsubst %.ml, obj/%.ml, $(ML_OBJ))

# Linear algebra objects
LA_DIR = $(ML_DIR)/LinearAlgebra
LA_OBJ = la_basic_types.la la_matrix.la la_matrix_like.la la_vector.la la_vector_overloads.la
LA_OBJ_FULL_PATH = $(patsubst la_%.la, obj/la_%.la, $(LA_OBJ))

# Train objects
TRAIN_OBJ = main.o funcs.o
TRAIN_OBJ_FULL_PATH = $(patsubst %.o, obj/%.o, $(TRAIN_OBJ))
TARGET = train.exe
BIN_DIR = ./bin
TARGET_FULL_PATH = $(BIN_DIR)/$(TARGET)

# Comprehensive list of all objects needed to build the target
ALL_OBJ = $(TRAIN_OBJ_FULL_PATH) $(ML_OBJ_FULL_PATH) $(LA_OBJ_FULL_PATH)

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -g -O2 -MMD -MP

# Includes
INCLUDES = -I. -I./inc -I./$(ML_DIR) -I./$(ML_DIR)/inc -I./../UnitTest/ -I./../UnitTest/inc -I./../confirm/inc -I./../confirm -I./$(LA_DIR)

# Rule for target
$(TARGET_FULL_PATH): $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ALL_OBJ) -o $(TARGET_FULL_PATH)

obj/%.o: src/%.cpp inc/%.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

obj/la_%.la: $(LA_DIR)/src/la_%.cpp $(LA_DIR)/src/la_%.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

obj/%.ml: $(ML_DIR)/src/%.cpp $(ML_DIR)/inc/%.h
	@echo "Now building $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# By default, only clean the objects from this project
clean:
	rm -f $(TRAIN_OBJ) $(TARGET_FULL_PATH)

clean_la:
	rm -f $(LA_OBJ_FULL_PATH)

clean_ml:
	rm -f $(ML_OBJ_FULL_PATH)

clean_all:
	$(MAKE) clean
	$(MAKE) clean_la
	$(MAKE) clean_ml

all: $(TARGET_FULL_PATH)

run: $(TARGET_FULL_PATH)
	$(TARGET_FULL_PATH) $(BIN_DIR)/tmpnet.nn $(BIN_DIR)/linear_dataset.td $(BIN_DIR)/out.nn 100

debug: $(TARGET_FULL_PATH)
	gdb -x gdb_cmd --args $(TARGET_FULL_PATH) $(BIN_DIR)/tmpnet.nn $(BIN_DIR)/linear_dataset.td $(BIN_DIR)/out.nn 100

.PHONY: clean run all clean_la la ml clean_ml debug