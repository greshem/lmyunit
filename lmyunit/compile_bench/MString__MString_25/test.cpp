#include <unitcode/mstring.h>

class MString_SubClass: public MString
{
public:
    MString_SubClass(MString const& In):MString(In){}
};//MString_SubClass

int main(int argc, char *argv[])
{
    MString In("In");
    MString_SubClass* string = new MString_SubClass(In); //target call
    return 0;
}
