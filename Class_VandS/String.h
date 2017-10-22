#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <cstring>
#include "Base.h"
class String:public Base<char>
{
public:
    String(int size=0,const char *x=NULL):Base<char>(size,x){}
    String(const char *str):Base<char>(strlen(str),str){}
    String(int n,const char &c) throw (double);//n不能小于0
    String(const String &v):Base<char>(v){}
    ~String();
    bool operator>(const String &v) const;
    bool operator<(const String &v) const;
    bool operator>=(const String &v) const;
    bool operator<=(const String &v) const;
    String operator+(const String &s) const;
    String operator+(const char &c) const;
    String & operator+=(const char &c);
    String & operator+=(const String &s);
    void Input();
    void Output()const;
};

String::~String()
{
    if(this->p!=NULL)
    {
        delete [] this->p;
        this->num=0;
        this->p=NULL;
    }
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
void String::Input()
{
    char *str;
    int n=0;
    if(cin.peek()!='\n') n++;
    str=new char[n];
    cin>>str;
    *this=str;
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
String String::operator+(const String &s) const
{
    String temp;
    temp.p=new char[this->num+s.num];
    temp.num=this->num+s.num;
    int i;
    for(i=0;i<this->num;++i)
    {
        temp.p[i]=this->p[i];
    }
    for(;i<this->num+s.num;++i)
    {
        temp.p[i]=s.p[i-this->num];
    }
    return temp;
}
String & String::operator+=(const String &s)
{
    *this=*this+s;
    return *this;
}
String::String(int n,const char &c) throw (double)
{
    if(n<0)
    {
        throw 0;
    }
    this->num=n;
    this->p=new char[this->num];
    for(int i=0;i<this->num;++i)
    {
        this->p[i]=c;
    }
}
String String::operator+(const char &c) const
{
    String t(1,c);
    String temp(*this);
    temp=temp+t;
    return temp;
}
String & String::operator+=(const char& c)
{
    *this=*this+c;
    return *this;
}
#endif // STRING_H
