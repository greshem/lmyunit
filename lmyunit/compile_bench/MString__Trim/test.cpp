#include <unitcode/mstring.h>
int main(int argc, char *argv[])
{
	MString test(" abc ");
	test.Trim();
    //MString::Trim("String"); //target call
    return 0;
}
