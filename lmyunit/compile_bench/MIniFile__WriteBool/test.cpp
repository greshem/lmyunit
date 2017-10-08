#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile* inifile = new MIniFile();
    MString Section("Section");
    MString Name("Name");
    inifile->WriteBool(Section, Name, true); //target call
    return 0;
}
