#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_TimeZoom *timezoom = new MFD_TimeZoom();
    delete(timezoom); //target call
    return 0;
}
