#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Amount *amount = new MFD_Amount();
    delete(amount); //target call
    return 0;
}
