#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MString DirTreeName("testdata/");
    MFile::CreateDirectoryTree(DirTreeName); //target call
    return 0;
}
