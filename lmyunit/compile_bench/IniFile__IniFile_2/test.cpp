#include <unitcode/IniFile.hpp>

class IniFile_SubClass: public IniFile
{
public:
    IniFile_SubClass(std::string const& filename, bool append):IniFile(filename, append){}
};//IniFile_SubClass

int main(int argc, char *argv[])
{
    std::basic_string<char> filename = "testdata/sample.txt";
    IniFile_SubClass* file = new IniFile_SubClass(filename, true); //target call
    return 0;
}
