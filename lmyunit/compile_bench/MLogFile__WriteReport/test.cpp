#include <unitcode/mlogfile.h>
int main(int argc, char *argv[])
{
    MLogFile* logfile = new MLogFile();
    char Source [] = {
        'B',
        'C',
        'D',
        'E',
        '\0'};
    char Content [] = {
        'F',
        'G',
        'H',
        'I',
        '\0'};
    logfile->WriteReport(
        'A',
        Source,
        Content,
        4); //target call
    return 0;
}
