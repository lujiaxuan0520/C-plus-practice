// Class_Complex.cpp
#include "Class_Complex.h"

Complex::Complex(double r,double i)
{
    real=r;imag=i;
}

double Complex:: get_real() const
{
    return real;
}

double Complex:: get_imag() const
{
    return imag;
}

void Complex:: SetComplex(double r,double i)
{
    real=r;imag=i;
}

void Complex:: Show() const
{
    cout<<real;
    if(imag==1) cout<<"+"<<"i"<<endl;
    else if(imag==-1) cout<<"-i"<<endl;
    else
    {
        if(imag>0) cout<<"+"<<imag<<"i"<<endl;
        else if(imag<0) cout<<imag<<"i"<<endl;
        else cout<<endl;
    }
}

double Complex:: radius() const
{
    return sqrt(real*real+imag*imag);
}

Complex operator+(const Complex& a,const Complex &b )
{
    Complex temp;
    temp.real=a.real+b.real;
    temp.imag=a.imag+b.imag;
    return temp;
}

Complex operator-(const Complex& a,const Complex &b )
{
    Complex temp;
    temp.real=a.real-b.real;
    temp.imag=a.imag-b.imag;
    return temp;
}
