#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Price* price = new MFD_Price();
    price->operator=(1); //target call
    return 0;
}
