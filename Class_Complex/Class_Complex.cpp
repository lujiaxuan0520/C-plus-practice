// Class_Complex.cpp
#include "Class_Complex.h"

Complex::Complex(double r,double i)     //构造函数
{
    real=r;imag=i;
}

Complex::Complex(const Complex& c)      //拷贝构造函数
{
    real=c.real;imag=c.imag;
}

double Complex:: get_real() const   //返回实部
{
    return real;
}

double Complex:: get_imag() const   //返回虚部
{
    return imag;
}

void Complex:: SetComplex(double r,double i)    //复数赋值
{
    real=r;imag=i;
}

void Complex:: Show() const     //输出复数
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

double Complex:: radius() const     //计算模长
{
    return sqrt(real*real+imag*imag);
}

Complex operator+(const Complex& a,const Complex &b )   //重载+运算符
{
    Complex temp;
    temp.real=a.real+b.real;
    temp.imag=a.imag+b.imag;
    return temp;
}

Complex operator-(const Complex& a,const Complex &b )   //重载-运算符
{
    Complex temp;
    temp.real=a.real-b.real;
    temp.imag=a.imag-b.imag;
    return temp;
}

ostream & operator<<(ostream &out,const Complex& c)     //重载<<运算符
{
    out<<c.real;
    if(c.imag==1) out<<"+"<<"i";
    else if(c.imag==-1) out<<"-i";
    else
    {
        if(c.imag>0) out<<"+"<<c.imag<<"i";
        else if(c.imag<0) out<<c.imag<<"i";

    }
    return out;
}

istream & operator>>(istream &in,Complex &c)        //重载>>运算符
{
    in>>c.real>>c.imag;
    return in;
}

Complex Complex::operator=(const Complex &c)
{
    this->real=c.real;this->imag=c.imag;
    return *this;
}

Complex Complex::operator+=(const Complex &b )
{
    this->real+=b.real;this->imag+=b.imag;
    return *this;
}

Complex Complex::operator-=(const Complex &b )
{
    this->real-=b.real;this->imag-=b.imag;
    return *this;
}

bool Complex::operator==(const Complex &b)
{
    if(this->real==b.real&&this->imag==b.imag) return 1;
    else return 0;
}
