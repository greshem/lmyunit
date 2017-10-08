#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MDll *dll = new MDll();
    delete(dll); //target call
    return 0;
}
