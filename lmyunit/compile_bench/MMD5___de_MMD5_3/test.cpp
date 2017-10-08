#include <lmyunit/unitlib.h>

class MMD5_SubClass: public MMD5
{
public:
    MMD5_SubClass():MMD5(){}
};//MMD5_SubClass

int main(int argc, char *argv[])
{
    MMD5_SubClass *d5 = new MMD5_SubClass();
    delete(d5); //target call
    return 0;
}
