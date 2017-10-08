#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MOptionTree *optiontree = new MOptionTree();
    delete(optiontree); //target call
    return 0;
}
