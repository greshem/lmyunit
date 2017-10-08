#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    MString Out;
    file->ReadString(&Out); //target call
    return 0;
}
