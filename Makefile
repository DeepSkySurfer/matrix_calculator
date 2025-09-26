CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
TARGET = test_app
SOURCES = src/matrix.cpp src/test.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: test clean