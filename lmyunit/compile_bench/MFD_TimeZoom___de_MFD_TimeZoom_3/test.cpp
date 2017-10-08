#include <lmyunit/unitlib.h>

class MFD_TimeZoom_SubClass: public MFD_TimeZoom
{
public:
    MFD_TimeZoom_SubClass():MFD_TimeZoom(){}
};//MFD_TimeZoom_SubClass

int main(int argc, char *argv[])
{
    MFD_TimeZoom_SubClass *timezoom = new MFD_TimeZoom_SubClass();
    delete(timezoom); //target call
    return 0;
}
