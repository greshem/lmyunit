#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_HighAmount* totalvolume = new MFD_HighAmount();
    totalvolume->operator=(1.5); //target call
    return 0;
}
