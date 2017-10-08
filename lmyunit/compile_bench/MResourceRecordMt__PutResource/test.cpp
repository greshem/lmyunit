#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MResourceRecordMt* resourcerecordmt = new MResourceRecordMt();
    resourcerecordmt->PutResource(1); //target call
    return 0;
}
