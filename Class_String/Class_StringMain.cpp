// Class_StringMain.cpp
#include <iostream>
#include <iomanip>
#include "Class_String.h"
using namespace std;

int main()
{
	String s("ed");
	String s1="vf";
	//s=s+s1;
	//cin>>s;
	//cout<<s<<endl<<s1<<endl;
	//s=s+s1;
	//cout<<s[0]<<s[1]<<s[2]<<s[3]<<s[4];
	cout<<(s+='a');

}
