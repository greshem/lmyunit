#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCRC16* mcrc16 = new MCRC16();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    mcrc16->CheckCode(InBuf, 4); //target call
    return 0;
}
