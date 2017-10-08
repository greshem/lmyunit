#include <lmyunit/unitlib.h>

class MIniFile_SubClass: public MIniFile
{
public:
    MIniFile_SubClass():MIniFile(){}

    void EndofAnsys_Wrapper() {
       char* InBuf = (char*) malloc(sizeof(char)*256);
       this->EndofAnsys(InBuf, 1);
    }
};//MIniFile_SubClass

int main(int argc, char *argv[])
{
    MIniFile_SubClass* inifile = new MIniFile_SubClass();
    inifile->EndofAnsys_Wrapper(); //target call
    return 0;
}
