#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MResourceRecordSt *resourcerecordst = new MResourceRecordSt();
    delete(resourcerecordst); //target call
    return 0;
}
