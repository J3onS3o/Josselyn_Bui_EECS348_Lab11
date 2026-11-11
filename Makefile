CXX      = g++
CXXFLAGS = -std=c++17 -Wall

all: attendance

attendance: attendance.cpp
	$(CXX) $(CXXFLAGS) attendance.cpp -o attendance

run: attendance
	./attendance

clean:
	rm -f attendance