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
    char Content [] = {
        'E',
        'F',
        'G',
        'H',
        '\0'};
    char DebugInfo [] = {
        'I',
        'J',
        'K',
        'L',
        '\0'};
    logfile->WriteDebug(
        Source,
        Content,
        DebugInfo,
        4); //target call
    return 0;
}
