#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Date *date = new MFD_Date();
    delete(date); //target call
    return 0;
}
