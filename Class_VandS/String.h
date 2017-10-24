#ifndef STRING_H
#define STRING_H
#include <iostream>
#include <cstring>
//#include "Base.h"
class String:public Base<char>
{
public:
    String(int size=0,const char *x=NULL):Base<char>(size,x){}
    String(const char *str):Base<char>(strlen(str),str){}
    String(int n,const char &c);
    String(const String &v):Base<char>(v){}
    bool operator<(const String &v) const;
    bool operator>(const String &v) const;
    bool operator<=(const String &v) const;
    bool operator>=(const String &v) const;
    String operator+(const String &s) const;            //两个字符串相加，与向量处理方法不同
    String operator+(const char &c) const;              //字符串加一个字符
    String & operator+=(const char &c);
    String & operator+=(const String &s);
    void Input(istream& in);
    void Output(ostream& out)const;
};

String::String(int n,const char &c)
{
    if(n<=0)
    {
        num = 0; p = NULL;
		return ;
    }
    this->num=n;
    this->p=new char[this->num];
    if(p==NULL)						//申请失败
	{
		num = 0;
		return ;
	}
    for(int i=0;i<this->num;++i)
    {
        this->p[i]=c;
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

String & String::operator+=(const String &s)
{
    *this=*this+s;
    return *this;
}

void String::Input(istream& in)
{
    char *str;
    int n=0;
    if(in.peek()!='\n') n++;
    str=new char[n];
    in>>str;
    *this=str;
}

void String::Output(ostream& out) const
{
    if(this->num == 0)
		out << "";
	else
	{
		for(int i=0; i<this->num; i++)
            {
                out << this->p[i];
            }
	}
}
#endif // STRING_H
