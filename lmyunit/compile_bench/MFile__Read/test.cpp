#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    char OutBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    file->Read(OutBuf, 4); //target call
    return 0;
}
