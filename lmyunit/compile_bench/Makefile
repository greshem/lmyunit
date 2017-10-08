CXX      = g++  -ftest-coverage -fprofile-arcs 
CXXFLAGS = -Wall
INCLUDES =  -I/root/lmyunit/ -I/root/lmyunit/lmyunit  -I/root/lmyunit/lmyunit/lmyunit

LIBS     =  /lib/libss.so.2 -L/root/lmyunit/lmyunit -lUnitLib -lpthread -ldl  -L /root/lmyunit/lmyunit/

all: test

test: test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) test.cpp -o test $(LIBS)

clean:
	rm -f test test.o
