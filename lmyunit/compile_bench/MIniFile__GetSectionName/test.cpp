#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile* inifile = new MIniFile();
    inifile->GetSectionName(1); //target call
    return 0;
}
