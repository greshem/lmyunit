#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MFD_Date* date = new MFD_Date();
    date->operator=(1); //target call
    return 0;
}
