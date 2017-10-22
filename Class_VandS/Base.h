#ifndef BASE_H
#define BASE_H
#include <iostream>
using namespace std;

template <typename T>
class Base
{
public:
	Base(int size=0, const T *x=NULL);			//���캯��
	Base(const Base<T> &v);                     //�������캯��
    virtual ~Base();                            //����������
    Base & operator=(const Base<T> &v);         //�ֵ���������

	int size() const;							//��ȡά��
    bool empty() const;                         //�ж��Ƿ�Ϊ��

	T & operator[](int index) const throw(char);//����������������±�Խ��ʱ�����쳣
	bool operator==(const Base<T> &v) const;
	bool operator!=(const Base<T> &v) const;

	virtual void Input() =0;                    //���뺯�����������ַ�������ʽ��ͬ
    virtual void Output() const = 0;            //����������������ַ�������ʽ��ͬ
    template <typename TYPE> friend ostream & operator<<(ostream &out,const Base<T> &B);
	template <typename TYPE> friend istream & operator>>(istream &in,Base<T> &B);
protected:
	int num;						// ά��
	T *p;							// ָ��������Դ�ռ���׵�ַ
};

template <typename T> Base<T>::Base(int size, const T *x)
{
	if(size<=0)
	{
		num = 0; p = NULL;
		return ;
	}
	p = new T[num=size];
	if(p==NULL)						//����ʧ��
	{
		num = 0;
		return ;
	}
	for(int i=0; i<num; i++)		// ������ɹ������õڶ�������׼��������Ԫ��Ϊ�������ַ�������ֵ
		p[i] = (x!=NULL ? x[i] : 0);// ���ڶ�������Ϊ�յ�ַ��NULL��������һ��nά0�������ַ�����
}

template <typename T> Base<T>::Base(const Base<T> &v) : num(0),p(NULL)
{
	*this = v;			            //ֱ�ӵ��ø�ֵ���������.���ڸ�ֵ�������������delete[]���������ȱ�֤pΪNULL
}

template <typename T> Base<T>::~Base()
{
	if(p!=NULL) delete [] p;
	num = 0;
	p = NULL;
}

template <typename T> Base<T> & Base<T>::operator=(const Base<T> &v)
{
	if(&v == this) return *this;
	if(p!=NULL) delete [] p;	    //�ͷ�ԭ�е���Դ
	if(v.num==0)
	{
		num = 0; p = NULL;
		return *this;
	}
	p = new T[num=v.num];
	if(p==NULL)					   //���벻�ɹ�������0ά����
	{
		num = 0;
		return *this;
	}
	for(int i=0; i<num; i++)
		p[i] = v.p[i];
	return *this;
}

template <typename T> int Base<T>::size() const
{
	return num;
}

template <typename T> bool Base<T>::empty() const
{
    if(num==0) return true;
    else return false;
}

template <typename T> T & Base<T>::operator[](int index) const throw(char)
{
	if(index<0 || index>=num)
		throw '\0';
	return p[index];
}

template <typename T> bool Base<T>::operator==(const Base<T> &v) const
{
	int i;
	if(num == v.num)
	{
		for(i=0; i<num; i++)
			if(p[i]!=v.p[i])
				break;
		return i<num ? false : true;
	}
	return false;
}

template <typename T> bool Base<T>::operator!=(const Base<T> &v) const
{
	return !(*this == v);
}

template <typename T> ostream & operator<<(ostream &out,const Base<T> &B)
{
    B.Output();
    return out;
}
template <typename T> istream & operator>>(istream &in, Base<T> &B)
{
    B.Input();
    return in;
}

#endif // Base_H
