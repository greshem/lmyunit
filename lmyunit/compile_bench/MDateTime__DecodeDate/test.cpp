#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MDateTime* datetime = new MDateTime(1);
    unsigned short* year = (unsigned short*) malloc(sizeof(unsigned short)*256);
    unsigned short* month = (unsigned short*) malloc(sizeof(unsigned short)*256);
    unsigned short* day = (unsigned short*) malloc(sizeof(unsigned short)*256);
    datetime->DecodeDate(year, month, day); //target call
    return 0;
}
