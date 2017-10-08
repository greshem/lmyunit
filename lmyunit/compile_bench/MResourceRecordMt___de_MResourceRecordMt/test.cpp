#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MResourceRecordMt *resourcerecordmt = new MResourceRecordMt();
    delete(resourcerecordmt); //target call
    return 0;
}
