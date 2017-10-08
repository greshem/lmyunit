#include <unitcode/mobject.h>
int main(int argc, char *argv[])
{
    MObject* object = new MObject();
    object->GetRuntimeClass(); //target call
    return 0;
}
