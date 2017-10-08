#include <lmyunit/unitlib.h>
int main(int argc, char *argv[])
{
    MOptionTree* optiontree = new MOptionTree();
    tagOptionTreeNode Parent = {
        4,
        {
            'A', 'B', 'C', 'D',
            'E', 'F', 'G', 'H',
            'I', 'J', 'K', 'L',
            'M', 'N', 'O', 'P',
            'Q', 'R', 'S', 'T',
            'U', 'V', 'W', 'X',
            'Y', 'Z', 'A', 'B',
            'C', 'D', 'E', 'F'},
        'G',
        4,
        4,
        {
            'H', 'I', 'J', 'K',
            'L', 'M', 'N', 'O',
            'P', 'Q', 'R', 'S',
            'T', 'U', 'V', 'W',
            'X', 'Y', 'Z', 'A',
            'B', 'C', 'D', 'E',
            'F', 'G', 'H', 'I',
            'J', 'K', 'L', 'M'},
        1,
        {
            'N', 'O', 'P', 'Q',
            'R', 'S', 'T', 'U',
            'V', 'W', 'X', 'Y',
            'Z', 'A', 'B', 'C',
            'D', 'E', 'F', 'G',
            'H', 'I', 'J', 'K',
            'L', 'M', 'N', 'O',
            'P', 'Q', 'R', 'S',
            'T', 'U', 'V', 'W',
            'X', 'Y', 'Z', 'A',
            'B', 'C', 'D', 'E',
            'F', 'G', 'H', 'I',
            'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q',
            'R', 'S', 'T', 'U',
            'V', 'W', 'X', 'Y',
            'Z', 'A', 'B', 'C',
            'D', 'E', 'F', 'G',
            'H', 'I', 'J', 'K',
            'L', 'M', 'N', 'O',
            'P', 'Q', 'R', 'S',
            'T', 'U', 'V', 'W',
            'X', 'Y', 'Z', 'A',
            'B', 'C', 'D', 'E',
            'F', 'G', 'H', 'I',
            'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q',
            'R', 'S', 'T', 'U',
            'V', 'W', 'X', 'Y',
            'Z', 'A', 'B', 'C',
            'D', 'E', 'F', 'G',
            'H', 'I', 'J', 'K'}};
    char Descript [] = {
        'N',
        'O',
        'P',
        'Q',
        '\0'};
    optiontree->AddNode(
        &Parent,
        "Name",
        'L',
        10,
        10,
        "SizeOfName",
        'M',
        Descript); //target call
    return 0;
}
