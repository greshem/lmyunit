#include <lmyunit/unitlib.h>

class MIniFile_SubClass: public MIniFile
{
public:
    MIniFile_SubClass():MIniFile(){}

    void SiftString_Wrapper() {
       char InString [] = {
           'A',
           'B',
           'C',
           'D',
           '\0'};
       this->SiftString(InString);
    }
};//MIniFile_SubClass

int main(int argc, char *argv[])
{
    MIniFile_SubClass* inifile = new MIniFile_SubClass();
    inifile->SiftString_Wrapper(); //target call
    return 0;
}
