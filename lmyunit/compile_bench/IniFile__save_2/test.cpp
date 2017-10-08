#include <iosfwd>
#include <ostream>
#include <unitcode/IniFile.hpp>

class std_basic_ios_char__SubClass: public std::basic_ios<char>
{
public:
    std_basic_ios_char__SubClass():std::basic_ios<char>(){}
};//std_basic_ios_char__SubClass

int main(int argc, char *argv[])
{
    IniFile* file = new IniFile();
    std::basic_ios<char>* ios = (std::basic_ios<char>*)new std_basic_ios_char__SubClass();
    std::streambuf* __sb = (std::streambuf*)ios->rdbuf();
    std::ostream out((std::ostream::__streambuf_type*)__sb);
    file->save(out); //target call
    return 0;
}
