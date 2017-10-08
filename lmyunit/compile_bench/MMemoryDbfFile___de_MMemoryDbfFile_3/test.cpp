#include <lmyunit/unitlib.h>

class MMemoryDbfFile_SubClass: public MMemoryDbfFile
{
public:
    MMemoryDbfFile_SubClass():MMemoryDbfFile(){}
};//MMemoryDbfFile_SubClass

int main(int argc, char *argv[])
{
    MMemoryDbfFile_SubClass *memorydbffile = new MMemoryDbfFile_SubClass();
    delete(memorydbffile); //target call
    return 0;
}
