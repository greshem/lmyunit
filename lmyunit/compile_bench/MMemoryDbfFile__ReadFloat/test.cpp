#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMemoryDbfFile* memorydbffile = new MMemoryDbfFile();
    float* Value = (float*) malloc(sizeof(float)*256);
    memorydbffile->ReadFloat("FieldName", Value); //target call
    return 0;
}
