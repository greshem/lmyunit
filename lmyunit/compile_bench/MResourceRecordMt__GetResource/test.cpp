#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MResourceRecordMt* resourcerecordmt = new MResourceRecordMt();
    resourcerecordmt->GetResource(); //target call
    return 0;
}
