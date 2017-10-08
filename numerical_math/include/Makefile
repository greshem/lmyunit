CC = g++ -g  -Wall 
EXEC = Extremum
OBJS = Extremum.o 
CFLAGS +=-I /root/numerical_math/include/   -Wno-write-strings
LDFLAGS += 
LIBS +=

all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

vim: 
	vim Extremum.cpp
exec: 
	 ./Extremum
log:
	 vim Extremum.log
gdb: 
	gdb ./Extremum
Extremum.o: Extremum.cpp
	$(CC) $(CFLAGS) -c Extremum.cpp
	gcc -S   $(CFLAGS) Extremum.cpp


clean:
	-rm -f $(EXEC) *.o *.s *.log
