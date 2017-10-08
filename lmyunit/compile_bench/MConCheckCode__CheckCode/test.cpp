#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MConCheckCode* concheckcode = new MConCheckCode();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    concheckcode->CheckCode(InBuf, 4); //target call
    return 0;
}
