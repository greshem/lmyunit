#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_WareType* waretype = new MFD_WareType();
    waretype->operator=('A'); //target call
    return 0;
}
