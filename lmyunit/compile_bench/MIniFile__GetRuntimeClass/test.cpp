#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile* inifile = new MIniFile();
    inifile->GetRuntimeClass(); //target call
    return 0;
}
