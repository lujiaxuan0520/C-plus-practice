// Class_String.h
#ifndef MY_CLASS_STRING_H
#define MY_CLASS_STRING_H

class String
{
public:
    //���캯��
    String();                                   //���캯����ʵ�ֳ�ʼ��string s;
    String(const char* chr);                    //���캯����ʵ�ֳ�ʼ��string s("abc");
    String(const unsigned n,const char c);      //���캯����ʵ�ֳ�ʼ��string s(3,'a');
    String(String &s);   //�����⣡����βθĳ�const���ͣ����Ǹ����Ժ���벻������[]����������غ�����ì��     //�������캯����ʵ�ֳ�ʼ��string a(b);
    //���������
    char& operator[](unsigned index);           //���������[]��ʵ��s[i]�±����

//private:
    char *pc;
    int num;
};

#endif
