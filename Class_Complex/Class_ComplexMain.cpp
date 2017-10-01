// Class_ComplexMain.cpp
// For testing
#include <iostream>
#include <iomanip>
#include "Class_Complex.h"
using namespace std;

int main()
{
	Complex c;
    c.SetComplex(3,4);
    Complex c1,c2,t1,t2;
    c1.SetComplex(4,-1);
    c2=c1;
    c2+=c1;
    t1=c2;
    t2=c1+c2;
    //t1+=c;
    cout<<t1<<endl;
    cout<<t2<<endl;
	return 0;
}
