#include <unitcode/mstring.h>
int main(int argc, char *argv[])
{
    MString* string = new MString("string");
    MString In("In");
    string->operator+=(In); //target call
    return 0;
}
