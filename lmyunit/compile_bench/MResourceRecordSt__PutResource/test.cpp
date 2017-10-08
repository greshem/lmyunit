#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MResourceRecordSt* resourcerecordst = new MResourceRecordSt();
    resourcerecordst->PutResource(1); //target call
    return 0;
}
