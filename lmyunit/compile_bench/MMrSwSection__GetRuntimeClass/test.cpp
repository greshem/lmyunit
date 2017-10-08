#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMrSwSection* mrswsection = new MMrSwSection();
    mrswsection->GetRuntimeClass(); //target call
    return 0;
}
