#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMrSwSection *mrswsection = new MMrSwSection();
    delete(mrswsection); //target call
    return 0;
}
