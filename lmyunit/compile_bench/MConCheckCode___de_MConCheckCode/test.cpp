#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MConCheckCode *concheckcode = new MConCheckCode();
    delete(concheckcode); //target call
    return 0;
}
