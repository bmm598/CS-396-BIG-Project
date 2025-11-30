# Simple Makefile for Geometry Engine
# Usage:
#   make        -> builds the executable (geometry_engine)
#   make clean  -> removes build artifacts
#	make test 	-> builds and runs the demo

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra 

SRCS := cpp/src/main.cpp cpp/src/parser.cpp cpp/src/geometry.cpp
BIN := cpp/src/geometry_engine

all: $(BIN)

$(BIN): $(SRCS)
	mkdir -p cpp/build
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRCS)

run: 
	./cpp/src/geometry_engine

clean:
	rm cpp/src/geometry_engine
	rm output.json
	rm queries.pl
	rm prolog/geometry.pl
