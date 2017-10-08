#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Amount* amount = new MFD_Amount();
    unsigned long BitOffset [] = {
        0,
        1,
        2,
        3};
    amount->WriteDataToBuf(BitOffset); //target call
    return 0;
}
