#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_SubULong *subulong = new MFD_SubULong();
    delete(subulong); //target call
    return 0;
}
