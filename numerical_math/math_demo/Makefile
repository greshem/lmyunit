CC = gcc -g  -Wall 
CPP = g++ -g  -Wall 
EXEC = inv  
MAIN_OBJS= inv.o  
NOMAIN_OBJS= 
CFLAGS +=-I /root/numerical_math/include/   -Wno-write-strings
LDFLAGS += 
LIBS +=

all: $(EXEC)
$(EXEC): $(MAIN_OBJS)  $(NOMAIN_OBJS) 
	$(CPP) $(LDFLAGS) -o $@ $@.o $(NOMAIN_OBJS) $(LIBS)

vim: 
	vim inv.cpp
exec: $(EXEC) 
	$(EXEC)
	./$@
log:
	 vim inv.log
gdb: 
	gdb ./inv
.PRECIOUS:%.cpp %.c %.C
.SUFFIXES:
.SUFFIXES:  .c .o .cpp .ecpp .pc .ec .C

.cpp.o:
	$(CPP) -c -o $*.o $(CFLAGS) $(INCLUDEDIR)  $*.cpp
	$(CPP) -S   $(CFLAGS) $(INCLUDEDIR)  $*.cpp

.c.o:
	$(CC) -c -o $*.o $(CFLAGS) $(INCLUDEDIR) $*.c
	$(CC) -S   $(CFLAGS) $(INCLUDEDIR) $*.c

.C.o:
	$(CC) -c -o $*.o $(CFLAGS) $(INCLUDEDIR) $*.C	
	$(CC) -S   $(CFLAGS) $(INCLUDEDIR) $*.C	

.ecpp.C:
	$(ESQL) -e $(ESQL_OPTION) $(INCLUDEDIR) $*.ecpp 
	
.ec.c:
	$(ESQL) -e $(ESQL_OPTION) $(INCLUDEDIR) $*.ec
	
.pc.cpp:
	$(PROC)  CPP_SUFFIX=cpp $(PROC_OPTION)  $*.pc
	

clean:
	-rm -f $(EXEC) *.o *.s *.log *.obj
