#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MBlockDataCompress* blockdatacompress = new MBlockDataCompress();
    blockdatacompress->GetRuntimeClass(); //target call
    return 0;
}
