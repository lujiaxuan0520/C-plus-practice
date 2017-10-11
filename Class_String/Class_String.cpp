// Class_String.cpp
#include "Class_String.h"
#include<cstdlib>
//以下为构造函数
String::String(const char* chr)
{
    if(!chr)
    {
        num=0;
        pc=NULL;
    }
    else
    {
        int i=0,_count=0;
        while(chr[i])
        {
            _count++;i++;
        }
        num=_count;
        pc=new char[num];
        if(pc==NULL)
        {
            num=0;pc=NULL;
            return;
        }
        else
        {
            for(i=0;i<num;++i)
            {
                pc[i]=chr[i];
            }
        }
    }
}

String::String(int n,const char &c) throw(char)
{
    if(n<0)
    {
        throw (char)0;
    }
    else
    {
        num=n;
        pc=new char[num];
        if(pc==NULL)
        {
            num=0;
            return;
        }
        else
        {
            for(int i=0;i<num;++i)
            {
                pc[i]=c;
            }
        }
    }
}

String::String(const String &s)
{
    if(s.num==0)
    {
        num=0;pc=NULL;
        return;
    }
    else
    {
        num=s.num;
        pc=new char[num];
        if(pc==NULL)
        {
            num=0;pc=NULL;
            return;
        }
        else
        {
            for(int i=0;i<num;++i)
            {
                pc[i]=s[i];
            }
        }
    }
}

//以下为析构函数
String::~String()
{
    if(pc!=NULL)
    {
        delete [] pc;
        num=0;
        pc=NULL;
    }
}

//以下为普通成员函数
int String::length() const
{
    return num;
}

bool String::empty() const
{
    if(num==0) return 1;
    else return 0;
}

String& String::erase()
{
    if(pc!=NULL)
    {
        delete [] pc;
        num=0;
        pc=NULL;
    }
    return *this;
}

String& String::swap(String &s)
{
	String temp = s;
	s=*this;
	*this=temp;
	return *this;
}

//以下为重载运算符
char& String::operator[](int index) const throw(double)
{
    if(index>=num)
    {
        throw (double)0;
    }
    else
    {
        return pc[index];
    }
}

String& String::operator=(const String& s)
{
    if(&s!=this)
    {
        if(pc!=NULL) delete [] pc;
        num=s.num;
        pc=new char[num];
        for(int i=0;i<num;++i)
        {
            pc[i]=s[i];
        }
    }
    return *this;
}

String String::operator+(const String& s) const
{
    String temp;
    temp.pc=new char[this->num+s.num];
    temp.num=this->num+s.num;
    int i;
    for(i=0;i<this->num;++i)
    {
        temp[i]=(*this)[i];
    }
    for(;i<this->num+s.num;++i)
    {
        temp[i]=s[i-this->num];
    }
    return temp;
}

String String::operator+(const char& c) const
{
    String t(1,c);
    String temp(*this);
    temp=temp+t;
    return temp;
}

String& String::operator+=(const String& s)
{
    *this=*this+s;
    return *this;
}

String& String::operator+=(const char& c)
{
    *this=*this+c;
    return *this;
}

bool String::operator==(const String &s) const
{
    if(this->num==s.num)
    {
        int i;
        for(i=0;i<s.num;++i)
        {
            if((*this)[i]!=s[i]) break;
        }
        if(i==s.num) return 1;
        else return 0;
    }
    else return 0;
}

bool String::operator!=(const String &s) const
{
    if(*this==s) return 0;
    else return 1;
}

bool String::operator<(const String& s) const
{
    if(*this==s) return 0;
    else if(this->num==0&&s.num!=0) return 1;
    else if(this->num!=0&&s.num==0) return 0;
    else
    {
        int _min=(this->num>s.num)?s.num:this->num;
        int i;
        for(i=0;i<_min;++i)
        {
            if((*this)[i]>s[i]) break;
        }
        if(i==_min) return 1;
        else return 0;
    }
}

bool String::operator>(const String& s) const
{
    if(*this==s) return 0;
    else if(this->num==0&&s.num!=0) return 0;
    else if(this->num!=0&&s.num==0) return 1;
    else
    {
        int _min=(this->num>s.num)?s.num:this->num;
        int i;
        for(i=0;i<_min;++i)
        {
            if((*this)[i]<s[i]) break;
        }
        if(i==_min) return 1;
        else return 0;
    }
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

ostream& operator<<(ostream& out,const String& s)
{
    for(int i=0;i<s.num;++i)
    {
        out<<s[i];
    }
    return out;
}

istream& operator>>(istream& in,String& s)
{
    in>>s.pc;
    char *it=s.pc;
    int _count=0;
    while(*it!='\0')
    {
        _count++;
        it++;
    }
    s.num=_count;
    return in;
}

