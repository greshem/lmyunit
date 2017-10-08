#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile* inifile = new MIniFile();
    MString Section("Section");
    MString Name("Name");
    MString Value("Value");
    inifile->WriteString(Section, Name, Value); //target call
    return 0;
}
