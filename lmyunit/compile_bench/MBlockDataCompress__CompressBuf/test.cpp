#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MBlockDataCompress* blockdatacompress = new MBlockDataCompress();
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
    blockdatacompress->CompressBuf(
        InBuf,
        8,
        (unsigned short) 0,
        (unsigned short) 0,
        OutBuf,
        4); //target call
    return 0;
}
