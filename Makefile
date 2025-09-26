CXX = g++
# Подавление специфических предупреждений
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Wno-comment

all: matrix_app test_app

matrix_app: src/matrix.cpp src/main.cpp
	$(CXX) $(CXXFLAGS) -o matrix_app src/matrix.cpp src/main.cpp

test_app: src/matrix.cpp src/test.cpp
	$(CXX) $(CXXFLAGS) -o test_app src/matrix.cpp src/test.cpp

test: test_app
	./test_app

clean:
	rm -f matrix_app test_app

.PHONY: all test clean