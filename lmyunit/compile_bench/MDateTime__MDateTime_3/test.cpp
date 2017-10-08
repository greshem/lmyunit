#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MDateTime In(1);
    MDateTime* datetime = new MDateTime(In); //target call
    return 0;
}
