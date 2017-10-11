// Class_StringMain.cpp
#include <iostream>
#include <iomanip>
#include "Class_String.h"
using namespace std;

int main()
{
    try
    {
        String s0 = "a";
        String s1("ab");
        String s2(1,'b');
        String s3 = s0;
        String s4 = s3+s0;
        cout << "s0 = " << s0 << endl;
        cout << "s1 = " << s1 << endl;
        cout << "s2 = " << s2 << endl;
        cout << "s3 = " << s3 << endl;
        cout << "s3 + s0 =" << s4 << endl;
        cout << "s2 += s1 :" << (s2+=s1) << endl;
        cout << "s2 += 'c':" << (s2+='c') << endl;
        cout << "s3 == s0 :" << (s3 == s0) << endl;
        cout << "s3 != s0 :" << (s3 != s0) << endl;
        cout << "s3 >= s0 :" << (s3 >= s0) << endl;
        cout << "s1 >= s0 :" << (s1 >= s0) << endl;
        cout << "s1 <= s0 :" << (s1 <= s0) << endl;
        cout << "s3 <= s0 :" << (s3 <= s0) << endl;
        cout << "s3 < s0 :" << (s3 < s0) << endl;
        cout << "s3 > s0 :" << (s3 > s0) << endl;
        cout << "s1[1] = " << s1[1] << endl;
        cout << "s3.length() :" << s3.length() << endl;
        s3.erase();
        cout << "s3.erase() :" << s3 << endl;
        s0.swap(s1);
        cout << "s0.swap(s1)" << endl << "s0 = " << s0 << ";s1 = " << s1 << endl;
    }
    catch(char)
    {
        cout<<"The first argument should be greater than zero.";
    }
    catch(double)
    {
        cout<<"Index too large";
    }
    return 0;
}
