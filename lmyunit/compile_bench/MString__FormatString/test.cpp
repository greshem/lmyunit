#include <unitcode/mstring.h>
int main(int argc, char *argv[])
{
    MString* string = new MString("string");
    string->FormatString("%d", 1, (char*)0); //target call
    return 0;
}
