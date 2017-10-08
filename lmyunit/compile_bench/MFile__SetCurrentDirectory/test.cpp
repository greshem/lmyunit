#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MString In("In");
    MFile::SetCurrentDirectory(In); //target call
    return 0;
}
