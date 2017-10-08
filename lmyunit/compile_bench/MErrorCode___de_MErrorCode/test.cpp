#include <unitcode/mobject.h>
int main(int argc, char *argv[])
{
    tagErrorCodeInfo ErrorTable = {1, "ClassName", "Content"};
    MErrorCode *errorcode = new MErrorCode(&ErrorTable);
    delete(errorcode); //target call
    return 0;
}
