#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MString FileName("testdata/sample.txt");
    MFile::IsExist(FileName); //target call
    return 0;
}
