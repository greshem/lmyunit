#include <unitcode/mstring.h>
int main(int argc, char *argv[])
{
    MString In1("In1");
    operator>(In1, "In2"); //target call
    return 0;
}
