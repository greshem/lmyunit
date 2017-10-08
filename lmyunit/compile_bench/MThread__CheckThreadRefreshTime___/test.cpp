#include <lmyunit/unitlib.h>

//auxiliary function
void
In(char* p1){}

int main(int argc, char *argv[])
{
    MThread::CheckThreadRefreshTime(&In); //target call
    return 0;
}
