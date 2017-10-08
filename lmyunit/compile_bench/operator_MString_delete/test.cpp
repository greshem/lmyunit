#include <stdlib.h>
#include <new>
int main(int argc, char *argv[])
{
    void* p1 = malloc(256);
    void* p2 = malloc(256);
    operator delete(p1, p2); //target call
    return 0;
}
