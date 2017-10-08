#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMD5* d5 = new MMD5();
    d5->MD5("inbuf", 1); //target call
    return 0;
}
