#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_HighAmount* totalvolume = new MFD_HighAmount();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    totalvolume->WriteDataToBuf(BitOffset); //target call
    return 0;
}
