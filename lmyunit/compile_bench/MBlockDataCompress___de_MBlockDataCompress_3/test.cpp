#include <lmyunit/unitlib.h>

class MBlockDataCompress_SubClass: public MBlockDataCompress
{
public:
    MBlockDataCompress_SubClass():MBlockDataCompress(){}
};//MBlockDataCompress_SubClass

int main(int argc, char *argv[])
{
    MBlockDataCompress_SubClass *blockdatacompress = new MBlockDataCompress_SubClass();
    delete(blockdatacompress); //target call
    return 0;
}
