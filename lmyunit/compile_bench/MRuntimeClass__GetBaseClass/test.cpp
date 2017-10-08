#include <lmyunit/unitlib.h>

//auxiliary function
MObject*
CreateObject(){
    return MOptionTree::CreateObject();
}

int main(int argc, char *argv[])
{
    MRuntimeClass* runtimeclass = new MRuntimeClass(
        "ClassName",
        9,
        &CreateObject,
        (MRuntimeClass*) NULL);
    runtimeclass->GetBaseClass(); //target call
    return 0;
}
