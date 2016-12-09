CXX:= g++
CXXFLAGS = -std=c++11 -g

SRC := $(wildcard *.cpp)
BIN := $(SRC:.cpp=)

all: $(BIN)

clean:
	$(RM) $(BIN)