#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    file->ReadWord(); //target call
    return 0;
}
