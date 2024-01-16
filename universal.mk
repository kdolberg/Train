# Compiler
CXX = g++

# Compiler flags
ifdef CXXFLAGS
	CXXFLAGS += -std=c++23 -Wall -g -O2 -MMD -MP
else
	CXXFLAGS = -std=c++23 -Wall -g -O2 -MMD -MP
endif

# Define all directory names
BINDIR = bin
DOCDIR = doc
OBJDIR = obj
INCDIR = inc
SANDIR = sandbox
SRCDIR = src
TESDIR = test
LIBDIR = lib
FOLDERS = $(BINDIR) $(DOCDIR) $(OBJDIR) $(INCDIR) $(SANDIR) $(SRCDIR) $(LIBDIR)

# Define repositories
LIBRARIES = MachineLearning MachineLearning/LinearAlgebra MachineLearning/LinearAlgebra/confirm ../UnitTest
REPOS = . $(LIBRARIES)
VPATH = $(REPOS)

# Include dependency files
DEP = $(wildcard $(OBJDIR)/*.d)
include $(DEP)

# Setup includes
_INCLUDE = $(INCDIR) $(addsuffix /inc,$(REPOS)) $(REPOS)
# Includes with the "-I" prefix added
INCLUDES = $(addprefix -I,$(_INCLUDE))

# All source code files
SRC = $(wildcard $(addsuffix /src/*.cpp,$(REPOS)))

# Target variable with full path
TARGET = $(addprefix $(BINDIR)/,$(_TARGET))

.DEFAULT_GOAL := $(TARGET)

# This variable contains the full path of all objects
OBJECTS = $(patsubst %.cpp,%$(OFX),$(addprefix $(OBJDIR)/, $(notdir $(SRC))))

# Rule to make the main target executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@echo -e "Building $(CL2)$(notdir $@)$(NC) (prereqs: $(CL2)$(sort $(notdir $^))$(NC))"
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) -o $(TARGET)
	@echo "done."

# Rule to make each object
$(OBJDIR)/%$(OFX): $(SRCDIR)/%.cpp $(INCDIR)/%.h
	@echo -e "Building $(CL1)$(notdir $@)$(NC) (prereqs: $(CL1)$(notdir $^)$(NC)) ... "
	@mkdir -p $(OBJDIR) $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to allow us to use the name of an object without including the full path on the command line
%$(OFX): $(OBJDIR)/%$(OFX)
	@echo "$@ ... done"

# Clean up all objects and executables
clean:
	rm -f $(OBJECTS) $(TARGET)

all: $(TARGET)

# Set the arguments with which to run the executable
ARGS = 1000

# Run the executable
run: $(TARGET)
	./$(TARGET).exe $(ARGS)

# Debug the executable using gdb
debug: $(TARGET)
	gdb --args $(TARGET) $(ARGS)

# Generate the folders for this project
folders:
	mkdir -p $(FOLDERS) $(addprefix $(TESDIR)/,$(FOLDERS))

libraries:
	@echo $(LIBRARIES)

dep:
	@echo $(DEP)

src:
	@echo $(SRC)

obj:
	@echo $(OBJECTS)

all_obj: $(OBJECTS)

clean_all:
	rm -f $(OBJECTS) $(DEP)

ndebug:
	$(MAKE) -f Makefile_ndebug.mk

ifdef MAKEFILES
makes:
	@echo $(MAKEFILES)
endif

.PHONY: clean run all folders libraries dep all_obj src obj clean_all print makes