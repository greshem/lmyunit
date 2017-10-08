#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MString FileName("testdata/sample.txt");
    MFile::GetFileAttributes(FileName); //target call
    return 0;
}
