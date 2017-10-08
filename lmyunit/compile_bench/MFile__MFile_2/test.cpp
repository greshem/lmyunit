#include <unitcode/mfile.h>

class MFile_SubClass: public MFile
{
public:
    MFile_SubClass():MFile(){}
};//MFile_SubClass

int main(int argc, char *argv[])
{
    MFile_SubClass* file = new MFile_SubClass(); //target call
    return 0;
}
