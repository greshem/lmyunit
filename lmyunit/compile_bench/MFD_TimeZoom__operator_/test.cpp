#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_TimeZoom* timezoom = new MFD_TimeZoom();
    timezoom->operator=('A'); //target call
    return 0;
}
