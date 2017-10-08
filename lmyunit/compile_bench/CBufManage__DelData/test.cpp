#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    CBufManage* bufmanage = new CBufManage(0);
    bufmanage->DelData(4, (long) 0); //target call
    return 0;
}
