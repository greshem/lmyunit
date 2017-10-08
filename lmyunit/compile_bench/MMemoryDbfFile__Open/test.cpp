#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMemoryDbfFile* memorydbffile = new MMemoryDbfFile();
    MString FileName("testdata/sample.txt");
    memorydbffile->Open(FileName); //target call
    return 0;
}
