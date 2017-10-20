#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <cstring>
#include "Base.h"
class String:public Base<char>
{
public:
    String(int size=0,const char *x=NULL);
    String();
    String(const char *str):Base<char>(strlen(str),str){}
    bool operator>(const String &v) const;
    bool operator<(const String &v) const;
};
String::String(int size,const char *x):Base<char>(size,x)
{
}
String::String()
{
    num=0;
    p=NULL;
}
bool String::operator<(const String& s) const
{
    if(*this==s) return 0;
    else if(this->num==0&&s.num!=0) return 1;
    else if(this->num!=0&&s.num==0) return 0;
    else
    {
        unsigned _min=(this->num>s.num)?s.num:this->num;
        unsigned i;
        for(i=0;i<_min;i++)
        {
            if((*this)[i]>s[i]) break;
        }
        if(i==_min&&s.num>this->num) return 1;
        else return 0;
    }
}
bool String::operator>(const String& s) const
{
    if(*this==s||*this<s) return 0;
    else return 1;
}
#endif // STRING_H
