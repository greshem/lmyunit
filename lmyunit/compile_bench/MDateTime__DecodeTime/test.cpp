#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MDateTime* datetime = new MDateTime(1);
    unsigned short* hour = (unsigned short*) malloc(sizeof(unsigned short)*256);
    unsigned short min = 0;
    unsigned short* sec = (unsigned short*) malloc(sizeof(unsigned short)*256);
    datetime->DecodeTime(hour, &min, sec); //target call
    return 0;
}
