# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++11

# Source files and executable
SRCS := main.cpp chessboard.cpp
EXE := chess_game

# Compile and link
all: $(EXE)

$(EXE): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Run the program
run: $(EXE)
	./$(EXE)

# Clean generated files
clean:
	rm -f $(EXE)

.PHONY: all run clean
