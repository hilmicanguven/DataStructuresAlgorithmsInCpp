/*

Recursion

*/


#include <iostream>
#include <vector>
 
using namespace std;


int factoriel(int n)
{
    if(n == 1) return 1;
    return n * factoriel(n-1);
}

int recursion_main()
{
    cout << "factoriel of " << 6 << " is: " << factoriel(6) << endl;

    return 0;
}