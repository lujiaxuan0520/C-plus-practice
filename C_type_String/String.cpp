//
//  String.cpp
//  class_String
//
//  Created by 王聪豪 on 2017/10/4.
//  Copyright © 2017年 王聪豪. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "String.h"
using namespace std;

String::String()
{
    l=0;
    str=new char[1];
    str[0]='\0';
}
String::~String()
{
    l=0;
    delete []str;
}
String::String(const char *cstr)
{
    l=strlen(cstr);
    str=new char[l+1];
    for(int i=0;i<l;i++)
        str[i]=cstr[i];
    str[l]='\0';
}
String::String(const String &cstr)
{
    l=cstr.l;
    str=new char[l+1];
    for(int i=0;i<l;i++)
        str[i]=cstr.str[i];
    str[l]='\0';
}
ostream &operator<<(ostream &os,const String &cstr)
{
    os<<cstr.str;
    return os;
}
istream &operator>>(istream &is,const String &cstr)
{
    is>>cstr.str;
    return is;
}
char &String::operator[](const int n)
{
    if(n>l) return str[l];
    else return str[n];
}
String &String::operator=(const String &cstr)
{
    delete []str;
    l=cstr.l;
    str=new char[l+1];
    for(int i=0;i<l;i++)
        str[i]=cstr.str[i];
    str[l]='\0';
    return *this;
}
String String::operator+(const String &cstr)
{
    String total;
    total.l=l+cstr.l;
    total.str=new char[total.l+1];
    for(int i=0;i<this->l;i++)
        total[i]=this->str[i];
    total[l]='\0';
    strcat(total.str,cstr.str);
    return total;
}
String &String::operator+=(const String &cstr)
{
    char *temp;
    temp=str;
    l=l+cstr.l;
    str=new char[l];
    strcpy(str, temp);
    strcat(str, cstr.str);
    delete []temp;
    return *this;
}
bool String::operator>(const String &cstr)
{
    return strcmp(str, cstr.str)>0;
}
bool String::operator<(const String &cstr)
{
    return strcmp(str, cstr.str)<0;
}
bool String::operator==(const String &cstr)
{
    return strcmp(str, cstr.str)==0;
}
bool String::operator!=(const String &cstr)
{
    return !(*this==cstr);
}
int String::Length()
{
    return l;
}
