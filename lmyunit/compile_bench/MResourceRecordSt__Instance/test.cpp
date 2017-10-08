#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MResourceRecordSt* resourcerecordst = new MResourceRecordSt();
    resourcerecordst->Instance(4); //target call
    return 0;
}
