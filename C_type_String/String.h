//
//  String.h
//  class_String
//
//  Created by 王聪豪 on 2017/10/4.
//  Copyright © 2017年 王聪豪. All rights reserved.
//

#ifndef String_h
#define String_h
#include <iostream>
using namespace std;

class String
{
public:
    String();
    ~String();
    String(const char *cstr);
    String(const String &cstr);
    friend ostream &operator<<(ostream &os,const String &cstr);
    friend istream &operator>>(istream &is,const String &cstr);
    char &operator[](const int n);
    String &operator=(const String &cstr);
    String operator+(const String &cstr);
    String &operator+=(const String &cstr);
    bool operator>(const String &cstr);
    bool operator<(const String &cstr);
    bool operator==(const String &cstr);
    bool operator!=(const String &cstr);
    int Length();
private:
    char *str;
    int l;
};

#endif /* String_h */
