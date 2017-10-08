#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMemoryDbfFile* memorydbffile = new MMemoryDbfFile();
    memorydbffile->WriteInteger("FieldName", 1); //target call
    return 0;
}
