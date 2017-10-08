#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    MString FileName("testdata/sample.txt");
    file->Create(FileName); //target call
    return 0;
}
