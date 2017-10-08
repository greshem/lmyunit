#include <unitcode/mlogfile.h>
int main(int argc, char *argv[])
{
    MLogFile* logfile = new MLogFile();
    logfile->GetRuntimeClass(); //target call
    return 0;
}
