#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MIniFile *inifile = new MIniFile();
    delete(inifile); //target call
    return 0;
}
