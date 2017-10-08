#include <lmyunit/unitlib.h>

class MIniFile_SubClass: public MIniFile
{
public:
    MIniFile_SubClass():MIniFile(){}

    tagIniFileSection* FindSection_Wrapper() {
       char Section [] = {
           'A',
           'B',
           'C',
           'D',
           '\0'};
       tagIniFileSection** LastSectionPtr = (tagIniFileSection**) malloc(sizeof(struct __INIFILESECTION)*256);
       return this->FindSection(Section, LastSectionPtr);
    }
};//MIniFile_SubClass

int main(int argc, char *argv[])
{
    MIniFile_SubClass* inifile = new MIniFile_SubClass();
    inifile->FindSection_Wrapper(); //target call
    return 0;
}
