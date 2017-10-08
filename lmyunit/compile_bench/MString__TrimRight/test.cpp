#include <unitcode/mstring.h>
int main(int argc, char *argv[])
{
	MString tmp("  String ");
    tmp.TrimRight(); //target call
    return 0;
}
