#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    CBufManage* bufmanage = new CBufManage(0);
    long len = 4;
    bufmanage->GetBufPtr((long&)len); //target call
    return 0;
}
