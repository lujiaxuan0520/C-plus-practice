// Class_ComplexMain.cpp
#include <iostream>
#include <iomanip>
#include "Class_Complex.h"
using namespace std;

int main()
{
	Complex c;
    c.SetComplex(3,4);
    Complex c1,t1,t2;
    c1.SetComplex(4,-1);
    t1=c+c1;
    t2=c-c1;
    t1.Show();
    t2.Show();
	return 0;
}
