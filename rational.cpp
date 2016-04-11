#include "rational.h"
#include <math.h>
#include <iostream>

Ration::Ration(int numer, int denomin){
    numerator = numer;
    denominator = denomin;
    revision();
}
Ration::Ration(const Ration& rat){
    numerator = rat.numer();
    denominator = rat.denomin();
}

Ration Ration::operator = (const Ration& rat){
    numerator = rat.numer();
    denominator = rat.denomin();
    return *this;
}
int Ration::numer() const{
    return numerator;
}

int Ration::denomin() const{
    return denominator;
}

void Ration::setNumerator(int a){
    numerator = a;
}

void Ration::setDenominator(int b){
    denominator = b;
}

Ration Ration::operator+ (const Ration& rat){
    int common_denominator = denomin()*rat.denomin() /
            NOK(denomin(), rat.denomin());
    int numerator = numer()*common_denominator/denomin() +
            rat.numer()*common_denominator/rat.denomin();
    Ration ratio(numerator, common_denominator);
    return ratio;
}

Ration Ration::operator- (const Ration& rat){
    int common_denominator = denomin()*rat.denomin() /
            NOK(denomin(), rat.denomin());
    int numerator = numer()*common_denominator/denomin() -
            rat.numer()*common_denominator/rat.denomin();
    Ration ratio(numerator, common_denominator);
    return ratio;
}

Ration Ration::operator* (const Ration& rat){
    int numer = numerator*rat.numer();
    int denomin = denominator*rat.denomin();
    Ration ratio(numer, denomin);
    return ratio;
}

Ration Ration::operator/ (const Ration& rat){
    Ration temp(rat.denomin(), rat.numer());
    return (*this)*temp;
}

Ration Ration::operator/ (const int& div){
    Ration temp(1, div);
    return (*this)*temp;
}

std::ostream& operator<< (std::ostream& os, const Ration& rat){
    if (rat.numer()%rat.denomin() == 0) os << rat.numer()/rat.denomin();
    else os << rat.numer() << "/" << rat.denomin();
    return os;
}

int Ration::NOK(int a, int b){
    return a*b/NOD(a, b);
}

int Ration::NOD(int dividend, int divider){
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

void Ration::revision(){
    int nod = NOD(numerator, denominator);
    numerator /= nod;
    denominator /= nod;
}




