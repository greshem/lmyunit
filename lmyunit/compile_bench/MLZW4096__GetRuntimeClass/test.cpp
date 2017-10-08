#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MLZW4096* mlzw4096 = new MLZW4096();
    mlzw4096->GetRuntimeClass(); //target call
    return 0;
}
