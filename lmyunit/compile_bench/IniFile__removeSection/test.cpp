#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    IniFile* file = new IniFile();
    std::basic_string<char> section = "section";
    file->removeSection(section); //target call
    return 0;
}
