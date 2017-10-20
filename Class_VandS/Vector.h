#ifndef VECTOR_H
#define VECTOR_H
#include"Base.h"
template <typename T>
class Vector:public Base<T>
{
public:
    Vector(int size=0,const T *x=NULL);
    Vector (const Vector<T> &v);
    Vector & operator=(const Vector<T> &v);
    Vector operator+(const Vector<T> &v) const throw(int);
    Vector & operator+=(const Vector<T> &v) throw(int);
    Vector & resize(int size);
    void Output()const;

};
template <typename T> Vector<T>::Vector(int size, const T *x):Base<T>(size,x)
{
    cout<<"V";
}
template <typename T> Vector<T>::Vector(const Vector<T> &v):Base<T>(v)
{
}
template <typename T> Vector<T> & Vector<T>::operator=(const Vector<T> &v)
{
    if(&v == this) return *this;// �������Ҹ�ֵʱ�Ķ�������������Ǵ���������������ֱ���ͷű��������Դ��
	if(this->p!=NULL)
        delete [] this->p;	// �����ͷű�����ԭ�е���Դ
	if(v.num==0)				// �����ֵ����Ϊ0ά����
	{
		this->num = 0; this->p = NULL;		// �򽫱��������0ά������ע�⣺ԭ������Դ�Ѿ����ͷţ�
		return *this;			// ���ر�����
	}
	this->p = new T[this->num=v.num];		// ��ʱ����ֵ����һ������0ά����������ֵ�����ά����Ʊ������ά�����������ʵ��Ķ��ڴ浥Ԫ
	if(this->p==NULL)					// ������벻�ɹ�����ֻ�ܷ���0ά����
	{
		this->num = 0;
		return *this;
	}
	for(int i=0; i<this->num; i++)	// ��ֵ��ֵ��Դ
		this->p[i] = v.p[i];
	return *this;				// ���ر�������ʹ��ֵ���ʽ�Ľ��Ϊ��ֵ������
}
template <typename T> Vector<T> Vector<T>::operator+(const Vector<T> &v) const throw(int)
{
	if(this->num != v.num)				// ά����ͬ���޷���ӡ�������һ�������쳣
		throw 1;
	Vector<T> temp(*this);
	for(int i=0; i<this->num; i++)
		temp.p[i] += v.p[i];
	return temp;					// ���ܸı�������������ֻ��ֵ���ض���
}
template <typename T> Vector<T> & Vector<T>::resize(int size)
{
	if(size <0 || size == this->num)			// ά�����䣬ֱ�ӷ��ر�����
		return *this;
	Vector<T> temp(size);
	for(int i=0; i<temp.num; i++)		// ά�����ܱ����С
		temp.p[i] = (i<this->num)? this->p[i] : 0;	// ��������ԭ�����ݣ�
	return *this=temp;					// ���ã����ֵ���������
}
template <typename T>void Vector<T>::Output() const
{
	if(this->num == 0)
		cout << "()";				// ��vΪ0ά������������һ��Բ����
	else
	{
		cout << '(' << this->p[0];		// ����ά�����ڻ����1����ô��������������ź͵�һ������
		for(int i=1; i<this->num; i++)	// ע��ѭ�����Ʊ���i��1��
            {
                cout << ", " << this->p[i];
            }
                cout << ')';
	}
}
template <typename T> Vector<T> & Vector<T>::operator+=(const Vector<T> &v) throw(int)
{
    *this=*this+v;
    return *this;
}
#endif // VECTOR_H
