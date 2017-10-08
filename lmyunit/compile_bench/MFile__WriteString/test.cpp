#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    MString In("In");
    file->WriteString(In); //target call
    return 0;
}
