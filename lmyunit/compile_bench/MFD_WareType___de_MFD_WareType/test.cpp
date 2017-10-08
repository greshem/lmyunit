#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_WareType *waretype = new MFD_WareType();
    delete(waretype); //target call
    return 0;
}
