// Class_Complex.h
#ifndef MY_CLASS_COMPLEX_H
#define MY_CLASS_COMPLEX_H
#include<cmath>
#include<iostream>
using namespace std;
class Complex
{
public:
    Complex(double r=0,double i=0);
    double get_real() const;
    double get_imag() const;
    void SetComplex(double r,double i);
    void Show() const;
    double radius() const;
private:
    double real;
    double imag;
} ;



#endif
