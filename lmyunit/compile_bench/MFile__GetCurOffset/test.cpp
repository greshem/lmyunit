#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    file->GetCurOffset(); //target call
    return 0;
}
