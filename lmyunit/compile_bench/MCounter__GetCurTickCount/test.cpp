#include <unitcode/mdatetime.h>
int main(int argc, char *argv[])
{
    MCounter* counter = new MCounter();
    counter->GetCurTickCount(); //target call
    return 0;
}
