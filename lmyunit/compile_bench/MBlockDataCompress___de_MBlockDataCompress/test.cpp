#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MBlockDataCompress *blockdatacompress = new MBlockDataCompress();
    delete(blockdatacompress); //target call
    return 0;
}
