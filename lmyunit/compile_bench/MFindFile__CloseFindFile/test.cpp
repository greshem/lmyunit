#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFindFile* findfile = new MFindFile();
    findfile->CloseFindFile(); //target call
    return 0;
}
