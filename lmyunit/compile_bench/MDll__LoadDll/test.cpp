#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MDll* dll = new MDll();
    MString DllPath("testdata/sample.txt");
    dll->LoadDll(DllPath); //target call
    return 0;
}
