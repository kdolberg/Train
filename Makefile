CXX = g++
CXXFLAGS = -std=c++23 -Wall -g -O2 -MMD -MP
INCLUDES = -I.
OBJECTS = # objects
TARGET = test

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) -o $(TARGET)

obj/%.o: src/%.cpp inc/%.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

all: $(TARGET)

run: $(TARGET)
	./$(TARGET).exe

.PHONY: clean run all\n