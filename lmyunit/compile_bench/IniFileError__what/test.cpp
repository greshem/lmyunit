#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    IniFileError* fileerror = new IniFileError("msg");
    fileerror->what(); //target call
    return 0;
}
