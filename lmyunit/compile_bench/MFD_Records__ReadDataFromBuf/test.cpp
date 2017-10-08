#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Records* records = new MFD_Records();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    records->ReadDataFromBuf(BitOffset); //target call
    return 0;
}
