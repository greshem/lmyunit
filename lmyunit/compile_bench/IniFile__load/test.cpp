#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    IniFile* file = new IniFile();
    std::basic_string<char> filename = "testdata/sample.txt";
    file->load(filename, true); //target call
    return 0;
}
