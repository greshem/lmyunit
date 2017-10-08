#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCriticalSection section;
    MCriticalSection::MLock lock(section);
    //target interface will be called at the end of main() function automatically
    return 0;
}
