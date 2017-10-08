#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MDateTime* datetime = new MDateTime(1);
    datetime->GetDayOfYear(); //target call
    return 0;
}
