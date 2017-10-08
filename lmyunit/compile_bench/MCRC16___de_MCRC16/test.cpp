#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MCRC16 *mcrc16 = new MCRC16();
    delete(mcrc16); //target call
    return 0;
}
