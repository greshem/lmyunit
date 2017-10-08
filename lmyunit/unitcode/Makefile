################OPTION###################
CCOMPILE = gcc -Wall
CPPCOMPILE = g++ -Wall
COMPILEOPTION = -c -g -static
INCLUDEDIR = 
LINK = ar
LINKOPTION = -r ../libUnitLib.a
LIBDIRS = 
OBJS = ./mthread.o ./msysteminfo.o ./mstring.o ./msrvcomm.o ./msocket.o ./mregister.o \
	   ./moptiontree.o ./mobject.o ./mmutex.o ./mlogfile.o ./mlzw.o ./minifile.o \
	   ./mfile.o ./mexcelfile.o ./mdll.o ./mdbffile.o ./mdatetime.o ./mdatastruct.o \
	   ./mdes.o ./mcheckcode.o ./mblockcompress.o ./mfinancedata.o \
		./die.o \
		./RandString.o \
		./tools.o \
		./IniFile.o \
		./BufManage.o
	
OUTPUT =  libUnitLib.a
APPENDLIB = 
PROC_OPTION = DEFINE=_PROC_ MODE=ORACLE LINES=true CODE=CPP
ESQL_OPTION = -g
################OPTION END################
ESQL = esql
PROC = proc
$(OUTPUT):$(OBJS) $(APPENDLIB)
	# mkdir ../libraray && true
	# mkdir ../libraray/debug && true
	# mkdir ../libraray/rlease &&true
	$(LINK) $(LINKOPTION) $(LIBDIRS)   $(OBJS) $(APPENDLIB)

clean: 
	rm -f $(OBJS)
	rm -f $(OUTPUT)
all: clean $(OUTPUT)
.PRECIOUS:%.cpp %.c %.C
.SUFFIXES:
.SUFFIXES:  .c .o .cpp .ecpp .pc .ec .C

.cpp.o:
	$(CPPCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR)  $*.cpp

.c.o:
	$(CCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR) $*.c

.C.o:
	$(CPPCOMPILE) -c -o $*.o $(COMPILEOPTION) $(INCLUDEDIR) $*.C	

.ecpp.C:
	$(ESQL) -e $(ESQL_OPTION) $(INCLUDEDIR) $*.ecpp 
	
.ec.c:
	$(ESQL) -e $(ESQL_OPTION) $(INCLUDEDIR) $*.ec
	
.pc.cpp:
	$(PROC)  CPP_SUFFIX=cpp $(PROC_OPTION)  $*.pc
