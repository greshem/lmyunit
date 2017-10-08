#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    IniFile* file = new IniFile();
    file->getSectionCount(); //target call
    return 0;
}
