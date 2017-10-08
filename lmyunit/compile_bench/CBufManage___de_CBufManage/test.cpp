#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    CBufManage *bufmanage = new CBufManage(0);
    delete(bufmanage); //target call
    return 0;
}
