#include <lmyunit/unitlib.h>

//auxiliary function
MObject*
CreateObject(){
    return MOptionTree::CreateObject();
}

int main(int argc, char *argv[])
{
    MMrSwSection* mrswsection = new MMrSwSection();
    MRuntimeClass* BaseClass = mrswsection->GetRuntimeClass();
    MRuntimeClass* runtimeclass = new MRuntimeClass(
        "ClassName",
        9,
        &CreateObject,
        BaseClass); //target call
    return 0;
}
