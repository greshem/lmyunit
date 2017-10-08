#include <unitcode/msocket.h>
int main(int argc, char *argv[])
{
    MSocket *msocket = new MSocket();
    delete(msocket); //target call
    return 0;
}
