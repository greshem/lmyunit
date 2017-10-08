CC = g++ -g  -Wall 
EXEC = check_free_space
OBJS = check_free_space.o 
CFLAGS +=-I /tmp2/trunk/Baselib/   -Wno-write-strings
LDFLAGS += 
LIBS += -lpthread

all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXEC) $(OBJS) $(LIBS)

vim: 
	vim check_free_space.cpp
exec: 
	 ./check_free_space
log:
	 vim check_free_space.log
gdb: 
	gdb ./check_free_space
check_free_space.o: check_free_space.cpp
	$(CC) $(CFLAGS) -c check_free_space.cpp
	gcc -S   $(CFLAGS) check_free_space.cpp


clean:
	-rm -f $(EXEC) *.o *.s *.log
