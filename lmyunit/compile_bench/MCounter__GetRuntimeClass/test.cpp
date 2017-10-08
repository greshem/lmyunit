#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MCounter* counter = new MCounter();
    counter->GetRuntimeClass(); //target call
    return 0;
}
