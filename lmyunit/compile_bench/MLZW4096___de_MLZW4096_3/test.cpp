#include <lmyunit/unitlib.h>

class MLZW4096_SubClass: public MLZW4096
{
public:
    MLZW4096_SubClass():MLZW4096(){}
};//MLZW4096_SubClass

int main(int argc, char *argv[])
{
    MLZW4096_SubClass *mlzw4096 = new MLZW4096_SubClass();
    delete(mlzw4096); //target call
    return 0;
}
