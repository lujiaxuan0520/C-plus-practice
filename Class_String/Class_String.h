// Class_String.h
#ifndef MY_CLASS_STRING_H
#define MY_CLASS_STRING_H
#include<iostream>
using namespace std;
class String
{
public:
    //构造函数
    String();                                   //构造函数，实现初始化string s;
    String(const char* chr);                    //构造函数，实现初始化string s("abc");
    String(const int n,const char c);           //构造函数，实现初始化string s(3,'a');
    String(const String &s);                    //拷贝构造函数，实现初始化string a(b);深拷贝
    //析构函数
    virtual ~String();                          //析构函数
    //普通成员函数
    int length() const;                         //返回字符串长度
    bool empty() const;                         //判断字符串是否为空
    String& erase();                            //清空字符串
    String& swap(String &s);                    //交换两个字符串
    //运算符重载
    char& operator[](unsigned index) const;     //重载[]运算符，实现s[i]下标访问
    String& operator=(const String& s);         //重载赋值运算符，实现s1=s2;深赋值
    String operator+(const String& s) const;    //重载加法运算符，实现s1+s2
    String operator+(const char& c) const;      //重载加法运算符，实现s+'a'
    String& operator+=(const String& s);        //重载+=运算符，实现s1+=s2
    String& operator+=(const char& c);          //重载+=运算符，实现s1+='a'
    bool operator==(const String &s) const;     //重载==运算符，实现s1==s2
    bool operator!=(const String &s) const;     //重载!=运算符，实现s1!=s2
    bool operator<(const String& s) const;      //重载<运算符，实现s1<s2
    bool operator>(const String& s) const;      //重载>运算符，实现s1>s2
    bool operator<=(const String& s) const;     //重载<=运算符，实现s1<=s2
    bool operator>=(const String& s) const;     //重载>=运算符，实现s1>=s2
    friend ostream& operator<<(ostream& out,const String& s);   //重载<<运算符
    friend istream& operator>>(istream& in,String& s);          //重载>>运算符
    //getline函数
    istream& getline(istream& in,String& s,int num);            //实现s.getline(cin,s,3);

private:
    char *pc;
    int num;
};

#endif
