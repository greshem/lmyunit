#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMemoryDbfFile *memorydbffile = new MMemoryDbfFile();
    delete(memorydbffile); //target call
    return 0;
}
