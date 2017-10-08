#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile* inifile = new MIniFile();
    MString Section("Section");
    MString Name("Name");
    inifile->ReadInteger(Section, Name, 1); //target call
    return 0;
}
