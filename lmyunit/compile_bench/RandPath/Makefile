#CXX      = g++  -Wl,--entry=main_gtest
CXX      = g++  
#CXX      = g++ -Wl,--entry=_Z10main_gtestiPPc
#-nostarfiles`
CXXFLAGS = -Wall
INCLUDES =  -I/root/lmyunit/lmyunit
LIBS     =  /lib/libss.so.2 -L/root/lmyunit/lmyunit -lUnitLib -lpthread -ldl -lgtest

all: test

test: test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) test.cpp -o test $(LIBS)

clean:
	rm -f test test.o
