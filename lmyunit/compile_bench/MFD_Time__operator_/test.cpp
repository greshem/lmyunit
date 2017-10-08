#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Time* mfd_time = new MFD_Time();
    mfd_time->operator=(1); //target call
    return 0;
}
