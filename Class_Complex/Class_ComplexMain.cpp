// Class_ComplexMain.cpp
#include <iostream>
#include <iomanip>
#include "Class_Complex.h"
using namespace std;

int main()
{
	Complex c;
    cout<<c.get_real()<<'\n'<<c.get_imag()<<endl;
    c.Show();
    c.SetComplex(3,2);
    cout<<c.get_real()<<'\n'<<c.get_imag()<<endl;
    c.Show();
    cout<<c.radius()<<endl;
	return 0;
}
