#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MResourceRecordMt* resourcerecordmt = new MResourceRecordMt();
    resourcerecordmt->Instance(4); //target call
    return 0;
}
