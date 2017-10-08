################OPTION###################
CCOMPILE = gcc -Wall  -fprofile-arcs -ftest-coverage 
CPPCOMPILE = g++ -Wall  -fprofile-arcs -ftest-coverage 
COMPILEOPTION = -c -g -static
INCLUDEDIR = 
LINK = ar
LINKOPTION = -r libUnitLib.a
SHARE_LINK = gcc -g -shared  
SHARE_LINKOPTION = -o libUnitLib.so

LIBDIRS = 
OBJS = unitcode/mthread.o unitcode/msysteminfo.o unitcode/mstring.o unitcode/msrvcomm.o unitcode/msocket.o unitcode/mregister.o \
	   unitcode/moptiontree.o unitcode/mobject.o unitcode/mmutex.o unitcode/mlogfile.o unitcode/mlzw.o unitcode/minifile.o \
	   unitcode/mfile.o unitcode/mexcelfile.o unitcode/mdll.o unitcode/mdbffile.o unitcode/mdatetime.o unitcode/mdatastruct.o \
	   unitcode/mdes.o unitcode/mcheckcode.o unitcode/mblockcompress.o unitcode/mfinancedata.o \
		unitcode/die.o \
		unitcode/RandString.o \
		unitcode/tools.o \
		unitcode/IniFile.o \
		unitcode/BufManage.o


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
	$(SHARE_LINK) $(SHARE_LINKOPTION) $(LIBDIRS)   $(OBJS) $(APPENDLIB)

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
