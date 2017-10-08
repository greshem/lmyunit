#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Bool* mfd_bool = new MFD_Bool();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    mfd_bool->WriteDataToBuf(BitOffset); //target call
    return 0;
}
