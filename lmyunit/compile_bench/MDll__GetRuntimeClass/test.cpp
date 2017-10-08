#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MDll* dll = new MDll();
    dll->GetRuntimeClass(); //target call
    return 0;
}
