#include <lmyunit/unitlib.h>

class MCriticalSection_SubClass: public MCriticalSection
{
public:
    MCriticalSection_SubClass():MCriticalSection(){}
};//MCriticalSection_SubClass

int main(int argc, char *argv[])
{
    MCriticalSection_SubClass *criticalsection = new MCriticalSection_SubClass();
    delete(criticalsection); //target call
    return 0;
}
