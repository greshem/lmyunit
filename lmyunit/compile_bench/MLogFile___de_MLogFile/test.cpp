#include <unitcode/mlogfile.h>
int main(int argc, char *argv[])
{
    MLogFile *logfile = new MLogFile();
    delete(logfile); //target call
    return 0;
}
