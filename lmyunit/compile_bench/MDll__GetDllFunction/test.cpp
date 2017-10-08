#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MDll* dll = new MDll();
    MString FunctionName("FunctionName");
    dll->GetDllFunction(FunctionName); //target call
    return 0;
}
