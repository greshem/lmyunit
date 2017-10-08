#include <unitcode/mstring.h>

class MString_SubClass: public MString
{
public:
    MString_SubClass(char const In, unsigned short const Count):MString(In, Count){}
};//MString_SubClass

int main(int argc, char *argv[])
{
    MString_SubClass* string = new MString_SubClass('A', 7); //target call
    return 0;
}
