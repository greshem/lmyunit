#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Price *price = new MFD_Price();
    delete(price); //target call
    return 0;
}
