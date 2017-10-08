#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_WareSerial* wareserial = new MFD_WareSerial();
    wareserial->operator=(1); //target call
    return 0;
}
