#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    CBufManage* bufmanage = new CBufManage(0);
    bufmanage->SetType(1); //target call
    return 0;
}
