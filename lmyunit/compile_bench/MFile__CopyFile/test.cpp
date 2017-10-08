#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MString SourceFile("testdata/sample.txt");
    MString NewFile("testdata/sample.txt");
    MFile::CopyFile(SourceFile, NewFile, true); //target call
    return 0;
}
