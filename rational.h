#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

class Ration{
private:
    int numerator;
    int denominator;
    void setNumerator(int);
    void setDenominator(int);
    void revision();
    int NOD(int a, int b);
    int NOK(int a, int b);
public:
    Ration(int nomin = 1, int denomin = 1);
    Ration(const Ration& rat);
    //Ration(const double& drat);
    int numer()const;
    int denomin()const;

    Ration operator = (const Ration& rat);
    //bool operator == (const Ration& rat);
    //bool operator == (const double& drat);
    //bool operator < (const Ration& rat);
    friend std::ostream& operator<< (std::ostream& os, const Ration& rat);
    friend std::ostream& operator>> (std::ostream& os, const Ration& rat);
    Ration operator+ (const Ration& rat);
    Ration operator- (const Ration& rat);
    Ration operator* (const Ration& rat);
    Ration operator/ (const Ration& rat);
    Ration operator/ (const int& div);

};
#endif // RATIONAL_H

