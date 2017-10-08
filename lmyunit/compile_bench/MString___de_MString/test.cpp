#include <unitcode/mstring.h>
int main(int argc, char *argv[])
{
    MString *string = new MString("In");
    delete(string); //target call
    return 0;
}
