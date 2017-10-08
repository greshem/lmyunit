#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    CBufManage* bufmanage = new CBufManage(0);
    bufmanage->GetBufPtr(); //target call
    return 0;
}
