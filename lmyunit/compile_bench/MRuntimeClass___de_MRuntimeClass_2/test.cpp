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
    MRuntimeClass runtimeclass(
        "ClassName",
        9,
        &CreateObject,
        BaseClass);
    //target interface will be called at the end of main() function automatically
    return 0;
}
