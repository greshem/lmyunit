#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MCounter *counter = new MCounter();
    delete(counter); //target call
    return 0;
}
