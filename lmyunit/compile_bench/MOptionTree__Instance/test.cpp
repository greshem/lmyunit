#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MOptionTree* optiontree = new MOptionTree();
    optiontree->Instance(4); //target call
    return 0;
}
