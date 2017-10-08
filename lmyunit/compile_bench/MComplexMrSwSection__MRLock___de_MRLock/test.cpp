#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MComplexMrSwSection section;
    int nRlt = 1;
    MComplexMrSwSection::MRLock mrlock(section, (int&)nRlt);
    //target interface will be called at the end of main() function automatically
    return 0;
}
