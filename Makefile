# MachineLearning objects

.DEFAULT_GOAL := default

ML_DIR = ./MachineLearning
ML_OBJ = activation_function.ml layer.ml net.ml save_load.ml types.ml
ML_OBJ_FULL_PATH = $(patsubst %.ml, obj/%.ml, $(ML_OBJ))

# Linear algebra objects
LA_DIR = $(ML_DIR)/LinearAlgebra
LA_OBJ = la_basic_types.la la_matrix.la la_matrix_like.la la_vector.la la_vector_overloads.la
LA_OBJ_FULL_PATH = $(patsubst la_%.la, obj/la_%.la, $(LA_OBJ))

TRAIN_SRC_FULL_PATH = $(wildcard src/*.cpp)

# Train objects
TRAIN_OBJ = $(patsubst src/%.cpp,%.o,$(TRAIN_SRC_FULL_PATH))
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
INCLUDES = -I. -I./inc -I./$(ML_DIR) -I./$(ML_DIR)/inc -I./../UnitTest/ -I./../UnitTest/inc -I./../confirm/inc -I./../confirm -I./$(LA_DIR) -I./$(LA_DIR)/inc

DEP = $(wildcard obj/*.d)
include $(DEP)

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
	rm -f $(TRAIN_OBJ_FULL_PATH) $(TARGET_FULL_PATH)

clean_la:
	rm -f $(LA_OBJ_FULL_PATH)

clean_ml:
	rm -f $(ML_OBJ_FULL_PATH)

clean_all:
	$(MAKE) clean
	$(MAKE) clean_la
	$(MAKE) clean_ml

all: $(TARGET_FULL_PATH)

linear_args = inputs/prev.nn inputs/dataset.td outputs/out.nn 100
xor_args = outputs/forxor.nn inputs/xor_dataset.td outputs/forxor.nn 100

run: $(TARGET_FULL_PATH) clean_saves
	$(TARGET_FULL_PATH) $(xor_args)

debug: $(TARGET_FULL_PATH)
	gdb -x gdb_cmd --args $(TARGET_FULL_PATH) $(xor_args) --silent

clean_saves:
	rm -f outputs/out.nn

obj:
	@echo $(ALL_OBJ)

update_compile_date:
	touch src/compile_date.cpp

dep:
	@echo $(DEP)

default: update_compile_date $(TARGET_FULL_PATH)

.PHONY: clean run all clean_la la ml clean_ml debug clean_all clean_saves obj update_compile_date dep default