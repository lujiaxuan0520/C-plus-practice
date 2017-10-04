// Class_StringMain.cpp
#include <iostream>
#include <iomanip>
#include "Class_String.h"
using namespace std;

int main()
{
	String s("ad");
	String s1("ad");
	if(s!=s1) cout<<1;
	else cout<<0;
	return 0;
}
