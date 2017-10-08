#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MLZW4096* mlzw4096 = new MLZW4096();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    char OutBuf [] = {
        'E',
        'F',
        'G',
        'H',
        '\0'};
    mlzw4096->CompressBuf(
        InBuf,
        4,
        OutBuf,
        4); //target call
    return 0;
}
