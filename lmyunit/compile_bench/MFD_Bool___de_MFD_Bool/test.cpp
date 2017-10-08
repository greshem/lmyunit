#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Bool *mfd_bool = new MFD_Bool();
    delete(mfd_bool); //target call
    return 0;
}
