#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFindFile* findfile = new MFindFile();
    tagFileFindFileInfo Out;
    findfile->FindFirstFile("testdata/sample.txt", &Out); //target call
    return 0;
}
