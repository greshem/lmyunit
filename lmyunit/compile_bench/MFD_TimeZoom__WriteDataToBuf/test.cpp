#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_TimeZoom* timezoom = new MFD_TimeZoom();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    timezoom->WriteDataToBuf(BitOffset); //target call
    return 0;
}
