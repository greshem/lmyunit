#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MResourceRecordSt* resourcerecordst = new MResourceRecordSt();
    resourcerecordst->Release(); //target call
    return 0;
}
