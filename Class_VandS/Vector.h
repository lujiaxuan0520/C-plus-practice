#ifndef VECTOR_H
#define VECTOR_H
#include"Base.h"
#include<cmath>
template <typename T>
class Vector:public Base<T>
{
public:
    Vector(int size=0,const T *x=NULL):Base<T>(size,x){}    
    Vector operator+(const Vector<T> &v) const throw(double);//������ӣ����ַ����Ĵ�������ͬ
    Vector & operator+=(const Vector<T> &v);
    Vector operator*(int n) const;                           //��������
    Vector operator*(const Vector<T> &v) const throw(double);//����ÿһλ��ӦԪ��������γɵ�����
    Vector &operator*=(int n);
    Vector &operator*=(const Vector<T> &v);                  //��Ϊ����*���������쳣
    T mol() const;                                           //������ģ
    T dot(const Vector<T> &v) const throw(double);           //����������
    Vector & resize(int size);
    void Input(istream& in);
    void Output(ostream& out)const;
    void f(){cout<<"Vector::f()"<<endl;}
};

template <typename T> Vector<T> Vector<T>::operator+(const Vector<T> &v) const throw(double)
{
	if(this->num != v.num)				// ά����ͬ���޷���ӡ�������һ���쳣
		throw (double)2;
	Vector<T> temp(*this);
	for(int i=0; i<this->num; i++)
		temp.p[i] += v.p[i];
	return temp;
}

template <typename T> Vector<T> & Vector<T>::operator+=(const Vector<T> &v)
{
    *this=*this+v;
    return *this;
}

template <typename T>Vector<T> Vector<T>::operator*(int n) const
{
    Vector<T> temp(*this);
    for(int i=0;i<this->num;i++)
    {
        temp.p[i]*=n;
    }
    return temp;
}

template <typename T>Vector<T> Vector<T>::operator*(const Vector<T> &v) const throw(double)
{
    if(this->num != v.num)
		throw (double)0;
    Vector<T> temp(*this);
    for(int i=0;i<this->num;i++)
    {
        temp.p[i]*=v.p[i];
    }
    return temp;
}

template <typename T>Vector<T> & Vector<T>::operator*=(int n)
{
    *this=*this*n;
    return *this;
}

template <typename T>Vector<T> & Vector<T>::operator*=(const Vector<T> &v)
{
    *this=*this*v;
    return *this;
}

template <typename T>T Vector<T>::mol() const
{
    T sum=0;
    for(int i=0;i<this->num;i++)
    {
        sum+=(*this)[i]*(*this)[i];
    }
    return sqrt(sum);
}

template <typename T>T Vector<T>::dot(const Vector<T> &v) const throw(double)
{
    if(this->num != v.num)
		throw (double)1;
    T product=0;
    for(int i=0;i<this->num;++i)
    {
        product+=(*this)[i]*v[i];
    }
    return product;
}

template <typename T> Vector<T> & Vector<T>::resize(int size)
{
	if(size <0 || size == this->num)			// ά�����䣬ֱ�ӷ��ر�����
		return *this;
	Vector<T> temp(size);
	for(int i=0; i<temp.num; i++)
		temp.p[i] = (i<this->num)? this->p[i] : 0;
	return *this=temp;
}

template <typename T> void Vector<T>::Input(istream& in)
{									// ���������и���ʵ��������������Զ���������չ����С��ά���Ĺ���
	const int N = 1;//1024;			// Nȡ��Сֵ1��Ϊ�˵��ԣ�ʵ��ʹ��ʱȡ1024
	T buffer[N];					// ����TYPE�������ݵĻ�������������N����
	int i, j, k;
	char ch;
	while(in.get()!='(')			// ���˵�'('��֮ǰ�������ַ�
        ;
	while(true)						// ���˵���Բ����֮��Ŀհ��ַ�
	{
		ch = in.peek();			// ͵����һ���ַ������Ƿ�Ϊ�հ��ַ�
		if(ch==' ' || ch=='\t' || ch=='\n' || ch=='\r')
			in.get(ch);			// ���ǿհ��ַ�������˵�������ȡ���ã�
		else
			break;					// ֱ�������ǿհ��ַ���������whileѭ��
	}
	if(in.peek()==')')				// ͵����һ���ַ�������')'
	{
	    in.get(ch);
		this->resize(0);			// ������v��ά�����ó�0ά
		return;					    // �˳���������������Ϊ0ά����
	}
	for(k=0; ch!=')'; k++)
	{
		for(i=0; i<N&&ch!=')'; i++)	// ��ȡ��Ϊ����������TYPE�����ݣ����뻺����buffer�У���һ���ַ�ch��ʵΪ���ţ�
			in >> buffer[i] >> ch; // ������buffer��(i<N)������')'�������ݵ������v����Դ��
		this->resize(k*N+i);		// ǰ���Ѿ���k�γ���������buffer��ÿ��N��TYPE�����ݣ��������ǵ�k+1�Σ���i��TYPE�����ݣ�
									// ��ע��reDim��������"����������ԭ������"�Ĺ���
		for(j=0; j<i; j++)
			(*this)[k*N+j] = buffer[j];	// ���������������صķ������������v[]��
	}
    return;                         // ���÷��ص�һ��ʵ�Σ���ʵ���������루�����������������͵ı��������������룩
}

template <typename T>void Vector<T>::Output(ostream& out) const
{
	if(this->num == 0)
		out << "()";
	else
	{
		out << '(' << this->p[0];
		for(int i=1; i<this->num; i++)
            {
                out << ", " << this->p[i];
            }
                out << ')';
	}
}

#endif // VECTOR_H
