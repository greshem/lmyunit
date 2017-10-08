#include <unitcode/mstring.h>

class MString_SubClass: public MString
{
public:
    MString_SubClass():MString(){}
};//MString_SubClass

int main(int argc, char *argv[])
{
    MString_SubClass* string = new MString_SubClass(); //target call
    return 0;
}
