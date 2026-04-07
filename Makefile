# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Target executable name
TARGET = in2post

# Default rule: build the target
all: $(TARGET)

# Build the target by compiling in2post.cpp.
# GenericStack.h includes GenericStack.cpp.
$(TARGET): in2post.cpp GenericStack.h GenericStack.cpp
	$(CXX) $(CXXFLAGS) in2post.cpp -o $(TARGET)

# Clean rule: remove the executable
clean:
	rm -f $(TARGET)
