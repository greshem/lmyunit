#include <unitcode/die.h>
int main(int argc, char *argv[])
{
    char format [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    die(format, NULL); //target call
    return 0;
}
