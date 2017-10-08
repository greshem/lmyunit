#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFindFile* findfile = new MFindFile();
    tagFileFindFileInfo Out;
    findfile->FindNextFile(&Out); //target call
    return 0;
}
