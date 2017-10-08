#include <unitcode/mobject.h>

class MErrorCode_SubClass: public MErrorCode
{
public:
    MErrorCode_SubClass(tagErrorCodeInfo* ErrorTable):MErrorCode(ErrorTable){}
};//MErrorCode_SubClass

int main(int argc, char *argv[])
{
    tagErrorCodeInfo ErrorTable = {1, "ClassName", "Content"};
    MErrorCode_SubClass *errorcode = new MErrorCode_SubClass(&ErrorTable);
    delete(errorcode); //target call
    return 0;
}
