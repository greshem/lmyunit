#include <unitcode/mstring.h>
int main(int argc, char *argv[])
{
    MString* string = new MString("string");
    string->SetAt(1, 'A'); //target call
    return 0;
}
