#include <unitcode/mfile.h>

class MFindFile_SubClass: public MFindFile
{
public:
    MFindFile_SubClass():MFindFile(){}

    bool MatchingString_Wrapper() {
       return this->MatchingString("lpszSour", "lpszMatch", true);
    }
};//MFindFile_SubClass

int main(int argc, char *argv[])
{
    MFindFile_SubClass* findfile = new MFindFile_SubClass();
    findfile->MatchingString_Wrapper(); //target call
    return 0;
}
