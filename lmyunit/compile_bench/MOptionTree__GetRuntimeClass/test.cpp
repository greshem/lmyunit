#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MOptionTree* optiontree = new MOptionTree();
    optiontree->GetRuntimeClass(); //target call
    return 0;
}
