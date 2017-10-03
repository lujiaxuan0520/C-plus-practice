// Class_StringMain.cpp
#include <iostream>
#include <iomanip>
#include "Class_String.h"
using namespace std;

int main()
{
	String s(3,'c');
	String s1(s);
	cout<<s.num<<endl;
	cout<<s1[0]<<s1[1];
	return 0;
}
