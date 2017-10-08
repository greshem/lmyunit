#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    IniFile* file = new IniFile();
    std::vector<std::string> out = RandWord(4);
    file->getSections(out); //target call
    return 0;
}
