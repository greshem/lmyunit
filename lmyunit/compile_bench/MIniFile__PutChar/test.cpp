#include <lmyunit/unitlib.h>

class MIniFile_SubClass: public MIniFile
{
public:
    MIniFile_SubClass():MIniFile(){}

    int PutChar_Wrapper() {
       char* InBuf = (char*) malloc(sizeof(char)*256);
       return this->PutChar('A', InBuf, 1);
    }
};//MIniFile_SubClass

int main(int argc, char *argv[])
{
    MIniFile_SubClass* inifile = new MIniFile_SubClass();
    inifile->PutChar_Wrapper(); //target call
    return 0;
}
