#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MDateTime* datetime = new MDateTime(1);
    datetime->SetDateTime("Sun, 06 Nov 1994 08:49:37 GMT"); //target call
    return 0;
}
