#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMemoryDbfFile* memorydbffile = new MMemoryDbfFile();
    memorydbffile->GetRuntimeClass(); //target call
    return 0;
}
