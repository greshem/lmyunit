#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMemoryDbfFile* memorydbffile = new MMemoryDbfFile();
    memorydbffile->WriteFloat("FieldName", 1.5f); //target call
    return 0;
}
