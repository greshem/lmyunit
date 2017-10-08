#include <iosfwd>
#include <istream>
#include <unitcode/IniFile.hpp>

class std_basic_ios_char__SubClass: public std::basic_ios<char>
{
public:
    std_basic_ios_char__SubClass():std::basic_ios<char>(){}
};//std_basic_ios_char__SubClass

class IniFile_SubClass: public IniFile
{
public:
    IniFile_SubClass():IniFile(){}

    void load_istream_Wrapper() {
       std::basic_ios<char>* ios = (std::basic_ios<char>*)new std_basic_ios_char__SubClass();
       std::streambuf* __sb = (std::streambuf*)ios->rdbuf();
       std::istream in((std::istream::__streambuf_type*)__sb);
       this->load_istream(in);
    }
};//IniFile_SubClass

int main(int argc, char *argv[])
{
    IniFile_SubClass* file = new IniFile_SubClass();
    file->load_istream_Wrapper(); //target call
    return 0;
}
