#include <unitcode/mlogfile.h>

class MLogFile_SubClass: public MLogFile
{
public:
    MLogFile_SubClass():MLogFile(){}
};//MLogFile_SubClass

int main(int argc, char *argv[])
{
    MLogFile_SubClass *logfile = new MLogFile_SubClass();
    delete(logfile); //target call
    return 0;
}
