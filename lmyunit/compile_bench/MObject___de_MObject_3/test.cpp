#include <unitcode/mobject.h>

class MObject_SubClass: public MObject
{
public:
    MObject_SubClass():MObject(){}
};//MObject_SubClass

int main(int argc, char *argv[])
{
    MObject_SubClass *object = new MObject_SubClass();
    delete(object); //target call
    return 0;
}
