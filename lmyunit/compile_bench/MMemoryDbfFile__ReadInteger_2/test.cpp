#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMemoryDbfFile* memorydbffile = new MMemoryDbfFile();
    int* Value = (int*) malloc(sizeof(int)*256);
    memorydbffile->ReadInteger((unsigned short) 0, Value); //target call
    return 0;
}
