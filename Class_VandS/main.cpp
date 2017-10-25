// VectorMain.cpp
#include <iostream>
#include <fstream>              // �����ļ�����
#include "Vector.h"
#include "String.h"
#include <conio.h>
using namespace std;

template <typename T>
void test(Vector<T> &v0, Vector<T> &v1, Vector<T> &v2, Vector<T> &x)
{
    cout << "v0 = " << v0 << "\nv1 = " << v1 << "\nv2 = " << v2 << "\nx = " << x << endl;
    v1 = v2;                                    // ��ֵ����
    cout << "\n��ֵ���� v1 = v2\nv1 = " << v1 << endl;

    try                                         // Ȧ�����������쳣�ĺ������ã�+��+=��
    {
        cout << "\n�����������" << endl;
        x = v1 + v2;                            // ��ʱv1��v2��������ȵ���������ά������ȵģ�������ӣ��������쳣
        cout << "x = v1 + v2\t" << x << endl;
        cout << "x += v1    \t" << (x += v1) << endl;

        cout << "\n����������� v0 + v1" << endl;
        x = v0 + v1;                            // v0��v1��ά������ͬ���޷���ӣ��������쳣������������佫����ִ��
        cout << "x = v0 + v1\t" << x << endl;
    }
    catch(double)                                  // ��׽�쳣��������
    {
        cout << "����ά����ͬ���޷���ӡ�" << endl;
    }
    do                                          // �����������
    {
        cout << "\n������һ��������������Բ���Ű�Χ�����ö��ŷָ������ĸ�������\n"
        << "����0ά��������()������" << endl;
        cin >> x;
        cout << x << endl;
    }while(x!=v0);                              // ����!=���������ĳ�(x.dim()!=0)
    cout << "\n������4�������޸ĳ�0ά�����������..." << endl;
    v0 = v1 = v2 = x.resize(0);
    cout << "v0 = " << v0 << "\nv1 = " << v1 << "\nv2 = " << v2 << "\nx = " << x << endl;
}
void test(int a)
{
    int array[] = {10, 50, 150};
    Vector<int> v0, v1(5), v2(3, array), x=v2;    // Ĭ�Ϲ���v0��ת������v1��һ�㹹��v2����������x
    cout << "���ͣ�int������Ϊ��������������" << endl;
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
    Vector<double> v0, v1(5), v2(3, array), x=v2;    // Ĭ�Ϲ���v0��ת������v1��һ�㹹��v2����������x
    cout << "�����ͣ�double������Ϊ��������������" << endl;
    test(v0, v1, v2, x);
}
//////////////////////
void testA(const char c)
{
    char array[] = "This is a string.";
    String v0, v1("Hello world."), v2(strlen(array)+1, array), x=v2;

    cout << "v0 = \"" << v0 << "\"\n"
    << "v1 = \"" << v1 << "\"\n"
    << "v2 = \"" << v2 << "\"\n"       // �ӹ��캯���ɼ��������ַ�������ʱ��β��׷�ӿո��ַ�(' ')
    << "x = \"" << x << "\"\n";

    cout << "\n�ַ�����ϵ����" << endl;
    cout << "v0 < v1\t\t" << boolalpha << (v0<v1) << endl;
    cout << "v2 < v1\t\t" << (v2<v1) << endl;
    cout << "x == v2\t\t" << (x == v2) << noboolalpha << endl;
    v1 = v2;
    cout << "\n��ֵ���� v1 = v2\nv1 = \"" << v1 << "\"\n";
    x = v1 + v2;
    cout << "\nƴ������ x = v1 + v2\t\"" << x << "\"\n";
    cout << "\nƴ�Ӹ�ֵ���� x += v1\t\"" << (x += v1) << "\"\n";

    x = v0 + v1;
    cout << "x = v0 + v1\t\"" << x << "\"" << endl;

    do
    {
        cout << "\n������һ���ַ�����ע��۲����е�5���ַ��Ƿ�����˴�Сдת����\n"
        << "���Ȳ���5�����쳣�����볢�����벻ͬ���ȵ��ַ�����q�˳�" << endl;
        cin >> x;
        cout << "\"" << x << "\"" << endl;
        try
        {
            cout << "�޸�������ַ����ĵ�5���ַ�����Сдת����" << endl;
            if('a'<=x[4] && x[4]<='z')
                x[4] -= 'a'-'A';
            else if('A'<=x[4] && x[4]<='Z')
                x[4] += 'a'-'A';
            cout << "\"" << x << "\"" << endl;
        }
        catch(char)
        {
            cout << "�±�Խ��" << endl;
        }
    }while(x.size()!=1 || x[0]!='q');
}
///////////////////////
int main()
{
    int key;
    while(true)
    {
        cout << "\n1--int, 2--double, 3--String, 4--�麯������, 0--exit: ";
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
