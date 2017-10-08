#include <stdlib.h>
#include <new>
int main(int argc, char *argv[])
{
    void* __p = malloc(256);
    operator new(4, __p); //target call
    return 0;
}
