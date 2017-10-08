#include <unitcode/msocket.h>

class MSocket_SubClass: public MSocket
{
public:
    MSocket_SubClass():MSocket(){}
};//MSocket_SubClass

int main(int argc, char *argv[])
{
    MSocket_SubClass *msocket = new MSocket_SubClass();
    delete(msocket); //target call
    return 0;
}
