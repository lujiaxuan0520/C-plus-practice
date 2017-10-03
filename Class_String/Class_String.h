// Class_String.h
#ifndef MY_CLASS_STRING_H
#define MY_CLASS_STRING_H

class String
{
public:
    //构造函数
    String();                                   //构造函数，实现初始化string s;
    String(const char* chr);                    //构造函数，实现初始化string s("abc");
    String(const unsigned n,const char c);      //构造函数，实现初始化string s(3,'a');
    String(String &s);   //有问题！想把形参改成const类型，但是改了以后编译不过，与[]的运算符重载函数相矛盾     //拷贝构造函数，实现初始化string a(b);
    //运算符重载
    char& operator[](unsigned index);           //重载运算符[]，实现s[i]下标访问

//private:
    char *pc;
    int num;
};

#endif
