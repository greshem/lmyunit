#include <unitcode/mlogfile.h>
int main(int argc, char *argv[])
{
    MLogFile* logfile = new MLogFile();
    MString FileName("testdata/sample.txt");
    logfile->Instance(FileName, 4); //target call
    return 0;
}
