#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    MString FileName("testdata/sample.txt");
    file->Open(FileName, (unsigned long) 0); //target call
    return 0;
}
