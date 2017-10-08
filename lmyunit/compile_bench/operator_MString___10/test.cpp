#include <ostream>
#include <iosfwd>
#include <unitcode/mstring.h>

class std_basic_ios_char__SubClass: public std::basic_ios<char>
{
public:
    std_basic_ios_char__SubClass():std::basic_ios<char>(){}
};//std_basic_ios_char__SubClass

int main(int argc, char *argv[])
{
    std::basic_ios<char>* ios = (std::basic_ios<char>*)new std_basic_ios_char__SubClass();
    std::streambuf* __sb = (std::streambuf*)ios->rdbuf();
    std::ostream in((std::ostream::__streambuf_type*)__sb);
    MString in2("in2");
    operator<<(in, in2); //target call
    return 0;
}
