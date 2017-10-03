// Class_String.cpp
#include "Class_String.h"
#include<iostream>
#include<cstdlib>

//����Ϊ���캯������
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

String::String(String &s)       //���޸ģ��β�const����
{
    num=s.num;
    pc=new char[num];
    for(unsigned i=0;i<num;++i)
    {
        pc[i]=s[i];
    }
}

//����Ϊ���������
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
