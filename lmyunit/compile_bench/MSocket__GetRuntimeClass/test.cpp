#include <unitcode/msocket.h>
int main(int argc, char *argv[])
{
    MSocket* msocket = new MSocket();
    msocket->GetRuntimeClass(); //target call
    return 0;
}
