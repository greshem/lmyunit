CC = gcc -g  -Wall 
CPP = g++ -g  -Wall 
EXEC = MatrixExample  matrix_contruct  MatrixRank  MatrixInv  
MAIN_OBJS= MatrixExample.o  matrix_contruct.o  MatrixRank.o  MatrixInv.o  
NOMAIN_OBJS= b.o g.o e.o f.o c.o a.o d.o h.o 
CFLAGS +=-I /root/numerical_math/include/  -I /root/numerical_math/include/  -I /root/numerical_math/include/  -I /root/trunk/Baselib/  -I /root/numerical_math/include/   -Wno-write-strings
LDFLAGS += 
LIBS += -lpthread  -lgtest 

all: $(EXEC)
$(EXEC): $(MAIN_OBJS)  $(NOMAIN_OBJS) 
	$(CPP) $(LDFLAGS) -o $@ $@.o $(NOMAIN_OBJS) $(LIBS)

vim: 
	vim MatrixExample.cpp
exec: $(EXEC) 
	$(EXEC
	./$@
log:
	 vim MatrixExample.log
gdb: 
	gdb ./MatrixExample
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
