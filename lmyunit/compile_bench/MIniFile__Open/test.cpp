#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile* inifile = new MIniFile();
    MString FileName("testdata/sample.txt");
    inifile->Open(FileName); //target call
    return 0;
}
