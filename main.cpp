#include <iostream>
#include <stdio.h>
#include <math.h>
#include <rational.h>
using namespace std;

int main()
{
    Ration rat1(17, 4);
    Ration rat2(37,4);
    Ration rat = rat1 + rat2;
    std::cout << rat << endl;
    getchar();
    return 0;
}
