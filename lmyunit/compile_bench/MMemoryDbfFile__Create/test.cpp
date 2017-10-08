#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMemoryDbfFile* memorydbffile = new MMemoryDbfFile();
    tagDbfField pDbfField = {
        {
            'A', 'B', 'C', 'D',
            'E', 'F', 'G', 'H',
            'I', 'J', 'K'},
        'L',
        (unsigned long) 0,
        'M',
        'N',
        {
            'O', 'P', 'Q', 'R',
            'S', 'T', 'U', 'V',
            'W', 'X', 'Y', 'Z',
            'A', 'B'}};
    memorydbffile->Create(
        "testdata/sample.txt",
        1,
        &pDbfField,
        0); //target call
    return 0;
}
