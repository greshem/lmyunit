#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    IniFileError *fileerror = new IniFileError("msg");
    delete(fileerror); //target call
    return 0;
}
