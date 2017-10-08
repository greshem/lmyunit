#include <unitcode/tools.h>
int main(int argc, char *argv[])
{
    char input [] = {
        'A',
        'B',
        'C',
        'D',
        '\0'};
    rand_mem_with_ascii_tools(input, 4); //target call
    return 0;
}
