#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    M3DES64* m3des64 = new M3DES64();
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
    m3des64->EncryptBuf(
        InBuf,
        4,
        OutBuf,
        Key); //target call
    return 0;
}
