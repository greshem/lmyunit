#include <unitcode/mfile.h>
int main(int argc, char *argv[])
{
    MFile* file = new MFile();
    MDateTime In(1);
    file->SetCreateDateTime(In); //target call
    return 0;
}
