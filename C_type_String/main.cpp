//
//  main.cpp
//  class_String
//
//  Created by 王聪豪 on 2017/10/4.
//  Copyright © 2017年 王聪豪. All rights reserved.
//

#include <iostream>
#include "String.h"
#include <string>
using namespace std;

int main()
{
    string s("hello"),sh("world"),ss;
    String c("HELLO"),ch("WORLD"),cc;
    ss=s+sh;
    cc=c+ch;
    cout<<"string:"<<s<<" + "<<sh<<" = "<<ss<<endl
    <<s<<" += "<<sh<<" = "<<(s+=sh)<<endl;
    cout<<"String:"<<c<<" + "<<ch<<" = "<<cc<<endl
    <<c<<" += "<<ch<<" = "<<(c+=ch)<<endl;
    return 0;
}
