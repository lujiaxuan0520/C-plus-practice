// Class_String.cpp
#include "Class_String.h"
#include<iostream>
#include<cstdlib>

//以下为构造函数定义
String::String()
{
    num=0;
    pc=nullptr;
}

String::String(const char* chr)
{
    if(!chr)
    {
        num=0;
        pc=nullptr;
    }
    else
    {
        unsigned i=0,_count=0;
        while(chr[i])
        {
            _count++;i++;
        }
        num=_count;
        pc=new char[num];
        for(i=0;i<num;++i)
        {
            pc[i]=chr[i];
        }
    }
}

String::String(unsigned n,const char c)
{
    num=n;
    pc=new char[num];
    for(unsigned i=0;i<num;++i)
    {
        pc[i]=c;
    }
}

String::String(String &s)       //待修改！形参const问题
{
    num=s.num;
    pc=new char[num];
    for(unsigned i=0;i<num;++i)
    {
        pc[i]=s[i];
    }
}

//以下为重载运算符
char& String::operator[](unsigned index)
{
    if(index>=num)
    {
        std::cerr<<"index too large";
        exit(-1);
    }
    else
    {
        return pc[index];
    }
}
