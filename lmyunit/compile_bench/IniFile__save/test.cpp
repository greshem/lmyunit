#include <unitcode/IniFile.hpp>
int main(int argc, char *argv[])
{
    IniFile* file = new IniFile();
    std::basic_string<char> filename = "testdata/sample.txt";
    file->save(filename, 1); //target call
    return 0;
}
