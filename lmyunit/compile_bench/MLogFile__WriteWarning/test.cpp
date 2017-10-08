#include <unitcode/mlogfile.h>
int main(int argc, char *argv[])
{
    MLogFile* logfile = new MLogFile();
    char Source [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    logfile->WriteWarning(
        Source,
        "%d",
        1,
        (char*)0); //target call
    return 0;
}
