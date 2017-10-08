#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile *file = new MFile();
    delete(file); //target call
    return 0;
}
