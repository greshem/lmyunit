#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SubULong* subulong = new MFD_SubULong();
    subulong->operator=(1); //target call
    return 0;
}
