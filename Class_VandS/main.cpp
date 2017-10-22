#include <iostream>
#include"Base.h"
#include"Vector.h"
#include"String.h"
using namespace std;

int main()
{
    double b[3]={1,2,3};
    double c[3]={2.4,4.1,6};
    Vector<double> a(3,b);
    Vector<double> d(3,c);

    cout<<a.dot(d);
//
//    String a(3,'b');
//
//    cout<<a.empty();
    return 0;
}
