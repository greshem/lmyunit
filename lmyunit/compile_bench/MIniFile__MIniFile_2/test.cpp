#include <lmyunit/unitlib.h>

class MIniFile_SubClass: public MIniFile
{
public:
    MIniFile_SubClass():MIniFile(){}
};//MIniFile_SubClass

int main(int argc, char *argv[])
{
    MIniFile_SubClass* inifile = new MIniFile_SubClass(); //target call
    return 0;
}
