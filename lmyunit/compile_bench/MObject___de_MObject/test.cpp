#include <unitcode/mobject.h>
int main(int argc, char *argv[])
{
    MObject *object = new MObject();
    delete(object); //target call
    return 0;
}
