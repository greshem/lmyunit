#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MDES64* mdes64 = new MDES64();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    char* OutBuf = (char*) malloc(sizeof(char)*256);
    char Key [] = {
        'E',
        'F',
        'G',
        'H',
        '\0'};
    mdes64->DecryptBuf(
        InBuf,
        4,
        OutBuf,
        Key); //target call
    return 0;
}
