#include <lmyunit/unitlib.h>

class MCriticalSection_MLock_SubClass: public MCriticalSection::MLock
{
public:
    MCriticalSection_MLock_SubClass(MCriticalSection& section):MCriticalSection::MLock(section){}
};//MCriticalSection_MLock_SubClass

int main(int argc, char *argv[])
{
    MCriticalSection section;
    MCriticalSection_MLock_SubClass *lock = new MCriticalSection_MLock_SubClass(section);
    delete(lock); //target call
    return 0;
}
