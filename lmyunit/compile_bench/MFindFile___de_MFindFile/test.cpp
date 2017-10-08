#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFindFile *findfile = new MFindFile();
    delete(findfile); //target call
    return 0;
}
