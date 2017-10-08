#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    file->LockFile(8, 4); //target call
    return 0;
}
