#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MDateTime* datetime = new MDateTime(1);
    MDateTime In(2);
    datetime->operator=(In); //target call
    return 0;
}
