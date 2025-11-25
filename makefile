# Simple Makefile for Geometry Engine
# Usage:
#   make        -> builds the executable (geometry_engine)
#   make clean  -> removes build artifacts
#	make test 	-> builds and runs the demo

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

SRCS := cpp/src/main.cpp cpp/src/parser.cpp cpp/src/geometry.cpp
BIN := cpp/build/geometry_engine

all: $(BIN)

$(BIN): $(SRCS)
	mkdir -p cpp/build
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRCS)

clean:
	rm -rf cpp/build

test: all
	./cpp/build/geometry_engine examples/triangle.json
