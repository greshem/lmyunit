#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MOptionTree* optiontree = new MOptionTree();
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    optiontree->GetExportBuf(8, OutBuf, 4); //target call
    return 0;
}
