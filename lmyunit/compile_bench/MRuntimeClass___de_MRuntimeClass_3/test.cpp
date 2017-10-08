#include <lmyunit/unitlib.h>

class MRuntimeClass_SubClass: public MRuntimeClass
{
public:
    MRuntimeClass_SubClass(
        char const* ClassName,
        int ClassSize,
        MObject*(*CreateObject)(),
        MRuntimeClass* BaseClass):MRuntimeClass(
            ClassName,
            ClassSize,
            CreateObject,
            BaseClass){}
};//MRuntimeClass_SubClass

//auxiliary function
MObject*
CreateObject(){
    return MOptionTree::CreateObject();
}

int main(int argc, char *argv[])
{
    MMrSwSection* mrswsection = new MMrSwSection();
    MRuntimeClass* BaseClass = mrswsection->GetRuntimeClass();
    MRuntimeClass_SubClass *runtimeclass = new MRuntimeClass_SubClass(
        "ClassName",
        9,
        &CreateObject,
        BaseClass);
    delete(runtimeclass); //target call
    return 0;
}
