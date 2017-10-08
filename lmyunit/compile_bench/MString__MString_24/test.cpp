#include <unitcode/mstring.h>

class MString_SubClass: public MString
{
public:
    MString_SubClass(char const* in, int length):MString(in, length){}
};//MString_SubClass

int main(int argc, char *argv[])
{
    MString_SubClass* string = new MString_SubClass("in", 2); //target call
    return 0;
}
