CXX      = g++
CXXFLAGS = -Wall
INCLUDES =  -I/usr/include/c\+\+
LIBS     =  /lib/libss.so.2 -L/root/lmyunit/lmyunit -lUnitLib -lpthread -ldl

all: test

test: test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) test.cpp -o test $(LIBS)

clean:
	rm -f test test.o
