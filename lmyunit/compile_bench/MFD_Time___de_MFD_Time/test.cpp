#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Time *mfd_time = new MFD_Time();
    delete(mfd_time); //target call
    return 0;
}
