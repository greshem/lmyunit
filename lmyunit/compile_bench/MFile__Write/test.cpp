#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    char InBuf [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    file->Write(InBuf, 4); //target call
    return 0;
}
