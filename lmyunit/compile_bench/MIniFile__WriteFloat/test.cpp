#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile* inifile = new MIniFile();
    MString Section("Section");
    MString Name("Name");
    inifile->WriteFloat(Section, Name, 1.5f); //target call
    return 0;
}
