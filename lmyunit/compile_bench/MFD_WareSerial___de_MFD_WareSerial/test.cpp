#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_WareSerial *wareserial = new MFD_WareSerial();
    delete(wareserial); //target call
    return 0;
}
