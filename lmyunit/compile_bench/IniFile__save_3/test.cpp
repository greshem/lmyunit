#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    IniFile* file = new IniFile();
    file->save(); //target call
    return 0;
}
