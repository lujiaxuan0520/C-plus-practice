#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <cstring>
#include "Base.h"
class String:public Base<char>
{
public:
    String(int size=0,const char *x=NULL);
    String(const char *str=""):Base<char>(strlen(str),str){}
    String(const String &v):Base<char>(v){}
    bool operator>(const String &v) const;
    bool operator<(const String &v) const;
    bool operator>=(const String &v) const;
    bool operator<=(const String &v) const;
    friend ostream & operator<<(ostream &out, const String &s);
    friend istream & operator>>(istream &in, String &s);
    void Output()const;
};
String::String(int size,const char *x):Base<char>(size,x)
{
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
            if((*this)[i]>s[i]) return 0;
            else if((*this)[i]<s[i]) return 1;
        }
        if(s.num>this->num) return 1;
        else return 0;
    }
}
bool String::operator>(const String& s) const
{
    if(*this==s||*this<s) return 0;
    else return 1;
}
bool String::operator<=(const String& s) const
{
    if(*this<s||*this==s) return 1;
    else return 0;
}
bool String::operator>=(const String& s) const
{
    if(*this>s||*this==s) return 1;
    else return 0;
}
ostream & operator<<(ostream &out, const String &s)
{
    out<<s.p;
    return out;
}
istream & operator>>(istream &in, String &s)
{
    char *str;
    int n=0;
    if(in.peek()!='\n') n++;
    str=new char[n];
    in>>str;
    s=str;
    return in;
}
void String::Output() const
{
    if(this->num == 0)
		cout << "";				// 若v为0维向量，则仅输出一对圆括号
	else
	{
		for(int i=0; i<this->num; i++)	// 注意循环控制变量i从1起
            {
                cout << this->p[i];
            }
	}
}
#endif // STRING_H
