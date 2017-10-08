#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MMrSwSection section;
    int nRlt = 1;
    MMrSwSection::MRLock mrlock(section, (int&)nRlt);
    //target interface will be called at the end of main() function automatically
    return 0;
}
