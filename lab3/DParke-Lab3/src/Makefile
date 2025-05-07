# Makefile for Huffman Encoding Program

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Directories
SRC_DIR = ./
OBJ_DIR = ./

# Files
SOURCES = $(SRC_DIR)main.cpp $(SRC_DIR)huffman.cpp
OBJECTS = $(OBJ_DIR)main.o $(OBJ_DIR)huffman.o
EXECUTABLE = huffman

# Default target
all: $(EXECUTABLE)

# Build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ_DIR)*.o $(EXECUTABLE)

# Run the program
run: $(EXECUTABLE)
	./$(EXECUTABLE) FreqTable.txt ClearText.txt Encoded.txt Decoded.txt

# Test targets
test1: $(EXECUTABLE)
	./$(EXECUTABLE) FreqTable.txt ClearText.txt Encoded.txt Decoded.txt

test2: $(EXECUTABLE)
	./$(EXECUTABLE) FreqTable2.txt ClearText2.txt Encoded2.txt Decoded2.txt

test3: $(EXECUTABLE)
	./$(EXECUTABLE) FreqTable3.txt ClearText3.txt Encoded3.txt Decoded3.txt

test4: $(EXECUTABLE)
	./$(EXECUTABLE) FreqTable4.txt ClearText4.txt Encoded4.txt Decoded4.txt

.PHONY: all clean run test1 test2 test3 test4