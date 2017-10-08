#include <unitcode/mfile.h>

class MFindFile_SubClass: public MFindFile
{
public:
    MFindFile_SubClass():MFindFile(){}

    int FindingString_Wrapper() {
       return this->FindingString("lpszSour", "lpszFind", 0);
    }
};//MFindFile_SubClass

int main(int argc, char *argv[])
{
    MFindFile_SubClass* findfile = new MFindFile_SubClass();
    findfile->FindingString_Wrapper(); //target call
    return 0;
}
