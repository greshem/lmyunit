#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile* inifile = new MIniFile();
    MString Section("Section");
    MString Name("Name");
    MString Default("Default");
    inifile->ReadString(Section, Name, Default); //target call
    return 0;
}
