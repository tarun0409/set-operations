#include <set>
#include <string.h>
#include <iostream>
#include "set.h"

using namespace std;

int main()
{
    srand(150);

    testCase1();

    //Inserting random elements then performing union. Testing using STL sets.
    testCase2();

    //Inserting 100 random elements then performing intersection. Testing using STL sets.
    testCase3();

    //Inserting 100 random elements then performing difference. Testing using STL sets.
    testCase4();

    return 0;

}
 