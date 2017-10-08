#include <unitcode/msocket.h>
int main(int argc, char *argv[])
{
    MSocket::SetSocketSync((long) 0); //target call
    return 0;
}
