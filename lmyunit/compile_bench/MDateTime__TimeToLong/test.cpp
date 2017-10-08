#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MDateTime* datetime = new MDateTime(1);
    datetime->TimeToLong(); //target call
    return 0;
}
