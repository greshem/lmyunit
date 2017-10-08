#include <unitcode/mobject.h>
int main(int argc, char *argv[])
{
    tagErrorCodeInfo ErrorTable = {1, "ClassName", "Content"};
    MErrorCode errorcode(&ErrorTable);
    //target interface will be called at the end of main() function automatically
    return 0;
}
