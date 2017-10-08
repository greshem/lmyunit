#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    IniFile* file = new IniFile();
    std::basic_string<char> section = "section";
    std::basic_string<char> key = "key";
    file->hasKey(section, key); //target call
    return 0;
}
