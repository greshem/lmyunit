#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Date* date = new MFD_Date();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    date->ReadDataFromBuf(BitOffset); //target call
    return 0;
}
