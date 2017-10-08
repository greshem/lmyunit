#include <unitcode/mstring.h>

class MString_SubClass: public MString
{
public:
    MString_SubClass(long const In):MString(In){}
};//MString_SubClass

int main(int argc, char *argv[])
{
    MString_SubClass* string = new MString_SubClass(1L); //target call
    return 0;
}
