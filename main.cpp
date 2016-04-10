#include <iostream>
#include <stdio.h>
#include <math.h>
#include <rational.h>
using namespace std;

int NOD(int dividend, int divider);
int NOK(int a, int b);
int main()
{
    Ration rat1(17, 4);
    Ration rat2(37,4);
    Ration rat = rat1 + rat2;
    std::cout << rat << endl;
    getchar();
    return 0;
}

int NOK(int a, int b){
    return a*b/NOD(a, b);
}

int NOD(int dividend, int divider){
    int temp = dividend;
    dividend = abs(dividend) > abs(divider)? dividend: divider;
    divider = abs(temp) < abs(divider)? temp: divider;
    while(temp != 0){
        temp = dividend%divider;
        dividend = divider;
        divider = temp;
    }
    return dividend;
}

