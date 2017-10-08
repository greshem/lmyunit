#include <unitcode/mstring.h>

class MString_SubClass: public MString
{
public:
    MString_SubClass(unsigned int const In):MString(In){}
};//MString_SubClass

int main(int argc, char *argv[])
{
    MString_SubClass* string = new MString_SubClass(1); //target call
    return 0;
}
