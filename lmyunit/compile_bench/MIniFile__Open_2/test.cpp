#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile* inifile = new MIniFile();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    inifile->Open(InBuf, 4); //target call
    return 0;
}
