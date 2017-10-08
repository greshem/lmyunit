#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMrSwSection* mrswsection = new MMrSwSection();
    mrswsection->LockRead(1); //target call
    return 0;
}
