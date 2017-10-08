#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_HighAmount *totalvolume = new MFD_HighAmount();
    delete(totalvolume); //target call
    return 0;
}
