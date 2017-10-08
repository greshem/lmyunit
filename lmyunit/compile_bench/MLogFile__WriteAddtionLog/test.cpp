#include <unitcode/mlogfile.h>
int main(int argc, char *argv[])
{
    MLogFile* logfile = new MLogFile();
    logfile->WriteAddtionLog("%d", 1, (char*)0); //target call
    return 0;
}
