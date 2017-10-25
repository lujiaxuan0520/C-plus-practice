// VectorMain.cpp
#include <iostream>
#include <fstream>              // 进行文件操作
#include "Vector.h"
#include "String.h"
#include <conio.h>
using namespace std;

template <typename T>
void test(Vector<T> &v0, Vector<T> &v1, Vector<T> &v2, Vector<T> &x)
{
    cout << "v0 = " << v0 << "\nv1 = " << v1 << "\nv2 = " << v2 << "\nx = " << x << endl;
    v1 = v2;                                    // 赋值运算
    cout << "\n赋值运算 v1 = v2\nv1 = " << v1 << endl;

    try                                         // 圈定可能抛掷异常的函数调用（+，+=）
    {
        cout << "\n两个向量相加" << endl;
        x = v1 + v2;                            // 此时v1与v2是两个相等的向量，其维数是相等的，可以相加，不抛掷异常
        cout << "x = v1 + v2\t" << x << endl;
        cout << "x += v1    \t" << (x += v1) << endl;

        cout << "\n两个向量相加 v0 + v1" << endl;
        x = v0 + v1;                            // v0与v1的维数不相同，无法相加，将抛掷异常，下面的输出语句将不被执行
        cout << "x = v0 + v1\t" << x << endl;
    }
    catch(double)                                  // 捕捉异常，并处理
    {
        cout << "向量维数不同，无法相加。" << endl;
    }
    do                                          // 向量输入测试
    {
        cout << "\n请输入一个向量，必须用圆括号包围，并用逗号分隔向量的各分量。\n"
        << "输入0维向量（即()）返回" << endl;
        cin >> x;
        cout << x << endl;
    }while(x!=v0);                              // 测试!=运算符。或改成(x.dim()!=0)
    cout << "\n将上述4个向量修改成0维向量，再输出..." << endl;
    v0 = v1 = v2 = x.resize(0);
    cout << "v0 = " << v0 << "\nv1 = " << v1 << "\nv2 = " << v2 << "\nx = " << x << endl;
}
void test(int a)
{
    int array[] = {10, 50, 150};
    Vector<int> v0, v1(5), v2(3, array), x=v2;    // 默认构造v0、转换构造v1、一般构造v2、拷贝构造x
    cout << "整型（int）数据为分量的向量测试" << endl;
    test( v0, v1, v2, x);
}
void test(float a)
{
    Vector<int> b;
    Base<int> *p1=&b,&q1=b;
    cout<<"Vector<int> b;"<<endl<<"Base<int> *p1=&b,&q1=b;"<<endl;
    cout<<"b.f()"<<endl;
    b.f();
    cout<<"p1->f()"<<endl;
    p1->f();
    cout<<"q1.f()"<<endl;
    q1.f();
    cout<<"=========================="<<endl;
    String c;
    Base<char> *p2=&c,&q2=c;
    cout<<"String c;"<<endl<<"Base<char> *p2=&c,&q2=c;"<<endl;
    cout<<"c.f()"<<endl;
    c.f();
    cout<<"p2->f()"<<endl;
    p2->f();
    cout<<"q2.f()"<<endl;
    q2.f();
}
void test(double a)
{
    double array[] = {1.414, 2.718, 3.142};
    Vector<double> v0, v1(5), v2(3, array), x=v2;    // 默认构造v0、转换构造v1、一般构造v2、拷贝构造x
    cout << "浮点型（double）数据为分量的向量测试" << endl;
    test(v0, v1, v2, x);
}
//////////////////////
void testA(const char c)
{
    char array[] = "This is a string.";
    String v0, v1("Hello world."), v2(strlen(array)+1, array), x=v2;

    cout << "v0 = \"" << v0 << "\"\n"
    << "v1 = \"" << v1 << "\"\n"
    << "v2 = \"" << v2 << "\"\n"       // 从构造函数可见，超出字符串长度时，尾部追加空格字符(' ')
    << "x = \"" << x << "\"\n";

    cout << "\n字符串关系运算" << endl;
    cout << "v0 < v1\t\t" << boolalpha << (v0<v1) << endl;
    cout << "v2 < v1\t\t" << (v2<v1) << endl;
    cout << "x == v2\t\t" << (x == v2) << noboolalpha << endl;
    v1 = v2;
    cout << "\n赋值运算 v1 = v2\nv1 = \"" << v1 << "\"\n";
    x = v1 + v2;
    cout << "\n拼接运算 x = v1 + v2\t\"" << x << "\"\n";
    cout << "\n拼接赋值运算 x += v1\t\"" << (x += v1) << "\"\n";

    x = v0 + v1;
    cout << "x = v0 + v1\t\"" << x << "\"" << endl;

    do
    {
        cout << "\n请输入一个字符串，注意观察其中第5个字符是否进行了大小写转换。\n"
        << "长度不足5，按异常处理。请尝试输入不同长度的字符串，q退出" << endl;
        cin >> x;
        cout << "\"" << x << "\"" << endl;
        try
        {
            cout << "修改输入的字符串的第5个字符（大小写转换）" << endl;
            if('a'<=x[4] && x[4]<='z')
                x[4] -= 'a'-'A';
            else if('A'<=x[4] && x[4]<='Z')
                x[4] += 'a'-'A';
            cout << "\"" << x << "\"" << endl;
        }
        catch(char)
        {
            cout << "下标越界" << endl;
        }
    }while(x.size()!=1 || x[0]!='q');
}
///////////////////////
int main()
{
    int key;
    while(true)
    {
        cout << "\n1--int, 2--double, 3--String, 4--虚函数特性, 0--exit: ";
        key = getch() - '0';
        cout << endl;
        if(key==0) break;
        switch(key)
        {
            case 1: test(int(0));           break;
            case 2: test(double(0));        break;
            case 3: testA(char(0));   break;
            case 4:test(float(0));    break;
        }
    }
    return 0;
}
