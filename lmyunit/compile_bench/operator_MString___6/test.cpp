#include <unitcode/mstring.h>
int main(int argc, char *argv[])
{
    MString In1("In1");
    MString In2("In2");
    operator>=(In1, In2); //target call
    return 0;
}
