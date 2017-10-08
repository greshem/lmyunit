#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Amount* amount = new MFD_Amount();
    amount->operator=(1.5f); //target call
    return 0;
}
