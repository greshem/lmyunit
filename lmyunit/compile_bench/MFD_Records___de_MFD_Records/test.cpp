#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Records *records = new MFD_Records();
    delete(records); //target call
    return 0;
}
