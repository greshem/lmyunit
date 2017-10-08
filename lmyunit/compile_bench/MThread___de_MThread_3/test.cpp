#include <lmyunit/unitlib.h>

class MThread_SubClass: public MThread
{
public:
    MThread_SubClass():MThread(){}
};//MThread_SubClass

int main(int argc, char *argv[])
{
    MThread_SubClass *thread = new MThread_SubClass();
    delete(thread); //target call
    return 0;
}
