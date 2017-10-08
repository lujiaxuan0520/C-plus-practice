// Class_StringMain.cpp
#include <iostream>
#include <iomanip>
#include "Class_String.h"
using namespace std;

int main()
{
	String s(2,'d');
	String s1="vf";
	s.swap(s1);
	s.erase();
	//s=s+s1;
	//cin>>s;
	//cout<<s<<endl<<s1<<endl;
	//s=s+s1;
	//cout<<s[0]<<s[1]<<s[2]<<s[3]<<s[4];
	cout<<s.empty()<<endl<<s1;
    return 0;
}
