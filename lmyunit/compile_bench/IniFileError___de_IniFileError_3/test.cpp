#include <unitcode/IniFile.hpp>

class IniFileError_SubClass: public IniFileError
{
public:
    IniFileError_SubClass(char const* msg):IniFileError(msg){}
};//IniFileError_SubClass

int main(int argc, char *argv[])
{
    IniFileError_SubClass *fileerror = new IniFileError_SubClass("msg");
    delete(fileerror); //target call
    return 0;
}
