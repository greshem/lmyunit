#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MString FileName("testdata/sample.txt");
    MFile::SetFileAttributes(FileName, 1); //target call
    return 0;
}
