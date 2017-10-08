#include <unitcode/mlogfile.h>
int main(int argc, char *argv[])
{
    MLogFile* logfile = new MLogFile();
    unsigned char Type [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    MString* Source = new MString("Source");
    MString* Content = new MString("Content");
    MDateTime* DateTime = new MDateTime(1);
    logfile->GetLogInfo(
        Type,
        Source,
        Content,
        DateTime); //target call
    return 0;
}
