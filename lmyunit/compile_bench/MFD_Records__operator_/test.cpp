#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Records* records = new MFD_Records();
    records->operator=(1); //target call
    return 0;
}
