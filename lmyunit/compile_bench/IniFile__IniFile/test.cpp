#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    std::basic_string<char> filename = "testdata/sample.txt";
    IniFile* file = new IniFile(filename, true); //target call
    return 0;
}
