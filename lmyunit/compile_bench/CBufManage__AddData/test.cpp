#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    CBufManage* bufmanage = new CBufManage(0);
    char buf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    bufmanage->AddData(buf, 4); //target call
    return 0;
}
