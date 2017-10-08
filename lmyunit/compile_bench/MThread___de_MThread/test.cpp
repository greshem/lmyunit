#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MThread *thread = new MThread();
    delete(thread); //target call
    return 0;
}
