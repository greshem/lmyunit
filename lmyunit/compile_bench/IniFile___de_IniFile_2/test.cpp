#include <unitcode/IniFile.hpp>

class IniFile_SubClass: public IniFile
{
public:
    IniFile_SubClass():IniFile(){}
};//IniFile_SubClass

int main(int argc, char *argv[])
{
    IniFile_SubClass *file = new IniFile_SubClass();
    delete(file); //target call
    return 0;
}
