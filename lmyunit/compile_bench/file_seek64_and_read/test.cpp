#include <unitcode/tools.h>
int main(int argc, char *argv[])
{
    FILE* file = fopen("testdata/sample.txt", "r+");
    int readLen = 0;
    file_seek64_and_read(
        file,
        8,
        4,
        &readLen); //target call

    //finalization
    fclose(file);

    return 0;
}
