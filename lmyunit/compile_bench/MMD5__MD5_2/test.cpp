#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMD5* d5 = new MMD5();
    char* OutBuf = (char*) malloc(sizeof(char)*256);
    d5->MD5("InBuf", 1, OutBuf); //target call
    return 0;
}
