#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    file->Seek(8, (unsigned long) 0); //target call
    return 0;
}
