#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMemoryDbfFile* memorydbffile = new MMemoryDbfFile();
    char Value [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    memorydbffile->FindRecord("FieldName", Value); //target call
    return 0;
}
