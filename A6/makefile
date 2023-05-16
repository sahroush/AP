CXX = g++
CXXFLAGS = -std=c++11 -Wall #-fsanitize=address -fsanitize=undefined
SRC_FILES = $(wildcard ./src/*.cpp)
OBJ_FILES = $(SRC_FILES:./src/%.cpp=./obj/%.o)
BIN_NAME = bin/snapp.out

.PHONY: clean
.PHONY: run

$(BIN_NAME): $(OBJ_FILES)
	mkdir -p ./bin
	$(CXX) $(OBJ_FILES) $(CXXFLAGS) -o $(BIN_NAME)

./obj/%.o: ./src/%.cpp
	mkdir -p ./obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf ./obj $(BIN_NAME)

run: $(BIN_NAME)
	$(BIN_NAME)