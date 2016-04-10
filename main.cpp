#include <iostream>
#include <stdio.h>
#include <math.h>
#include <rational.h>
using namespace std;

int main()
{
    int a = 1, b = 1;
    scanf("%d/%d", &a, &b);
    Ration rat1(a, b);
    scanf("%d/%d", &a, &b);
    Ration rat2(a,b);
    std::cout << "addition:\t" << rat1 + rat2 << endl;
    std::cout << "subtraction:\t" << rat1 - rat2 << endl;
    std::cout << "multiplication:\t" << rat1 * rat2 << endl;
    std::cout << "division:\t" << rat1 / rat2 << endl;
    cin.get();
    return 0;
}
