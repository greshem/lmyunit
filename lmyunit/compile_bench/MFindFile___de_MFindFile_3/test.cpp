#include <unitcode/mfile.h>

class MFindFile_SubClass: public MFindFile
{
public:
    MFindFile_SubClass():MFindFile(){}
};//MFindFile_SubClass

int main(int argc, char *argv[])
{
    MFindFile_SubClass *findfile = new MFindFile_SubClass();
    delete(findfile); //target call
    return 0;
}
