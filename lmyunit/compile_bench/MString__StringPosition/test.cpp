#include <unitcode/mstring.h>
int main(int argc, char *argv[])
{
    MString* string = new MString("string");
    string->StringPosition("In"); //target call
    return 0;
}
