#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MConCheckCode* concheckcode = new MConCheckCode();
    concheckcode->GetRuntimeClass(); //target call
    return 0;
}
