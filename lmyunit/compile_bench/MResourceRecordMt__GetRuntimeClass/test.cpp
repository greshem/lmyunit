#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MResourceRecordMt* resourcerecordmt = new MResourceRecordMt();
    resourcerecordmt->GetRuntimeClass(); //target call
    return 0;
}
