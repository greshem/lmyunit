#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    file->SetFileLength(4); //target call
    return 0;
}
