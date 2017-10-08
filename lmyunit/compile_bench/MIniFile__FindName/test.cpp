#include <lmyunit/unitlib.h>

class MIniFile_SubClass: public MIniFile
{
public:
    MIniFile_SubClass():MIniFile(){}

    tagIniFileValue* FindName_Wrapper() {
       tagIniFileValue** LastNamePtr = (tagIniFileValue**) malloc(sizeof(struct __INIFILEVALUE)*256);
       return this->FindName("Name", LastNamePtr);
    }
};//MIniFile_SubClass

int main(int argc, char *argv[])
{
    MIniFile_SubClass* inifile = new MIniFile_SubClass();
    inifile->FindName_Wrapper(); //target call
    return 0;
}
