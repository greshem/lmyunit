#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Time* mfd_time = new MFD_Time();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    mfd_time->ReadDataFromBuf(BitOffset); //target call
    return 0;
}
