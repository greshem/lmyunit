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
    memorydbffile->ReadString((unsigned short) 0, Value, 4); //target call
    return 0;
}
