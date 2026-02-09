.PHONY: all

CXX := g++
CXXFLAGS := -std=c++0x -O3 -Wall

all: main
	./main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

test: main input.txt
	./main < input.txt

.PHONY: clean

clean:
	rm main
