#ifndef VECTOR_H
#define VECTOR_H
#include"Base.h"
template <typename T>
class Vector:public Base<T>
{
public:
    Vector(int size=0,const T *x=NULL):Base<T>(size,x){}
    Vector (const Vector<T> &v):Base<T>(v){}
    ~Vector();
//    Vector & operator=(const Vector<T> &v);   //�о���ֵ��������Լ̳�
    Vector operator+(const Vector<T> &v) const throw(int);  //������ӣ����ַ����Ĵ�������ͬ
    Vector & operator+=(const Vector<T> &v);
    Vector operator*(int n) const;                          //��������
    Vector operator*(const Vector<T> &v) const throw(float);//����ÿһλ��ӦԪ��������γɵ�����
    Vector &operator*=(int n);
    Vector &operator*=(const Vector<T> &v);                 //��Ϊ����*���������쳣
    T dot(const Vector<T> &v) const throw(float);           //����������
    Vector & resize(int size);
    void Input();
    void Output()const;
};

template <typename T> Vector<T>::~Vector()
{
    if(this->p!=NULL)
    {
        delete [] this->p;
        this->num=0;
        this->p=NULL;
    }
}
//template <typename T> Vector<T> & Vector<T>::operator=(const Vector<T> &v)
//{
//    if(&v == this) return *this;// �������Ҹ�ֵʱ�Ķ�������������Ǵ���������������ֱ���ͷű��������Դ��
//	if(this->p!=NULL)
//        delete [] this->p;	// �����ͷű�����ԭ�е���Դ
//	if(v.num==0)				// �����ֵ����Ϊ0ά����
//	{
//		this->num = 0; this->p = NULL;		// �򽫱��������0ά������ע�⣺ԭ������Դ�Ѿ����ͷţ�
//		return *this;			// ���ر�����
//	}
//	this->p = new T[this->num=v.num];		// ��ʱ����ֵ����һ������0ά����������ֵ�����ά����Ʊ������ά�����������ʵ��Ķ��ڴ浥Ԫ
//	if(this->p==NULL)					// ������벻�ɹ�����ֻ�ܷ���0ά����
//	{
//		this->num = 0;
//		return *this;
//	}
//	for(int i=0; i<this->num; i++)	// ��ֵ��ֵ��Դ
//		this->p[i] = v.p[i];
//	return *this;				// ���ر�������ʹ��ֵ���ʽ�Ľ��Ϊ��ֵ������
//}

template <typename T> Vector<T> Vector<T>::operator+(const Vector<T> &v) const throw(int)
{
	if(this->num != v.num)				// ά����ͬ���޷���ӡ�������һ�������쳣
		throw 1;
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

template <typename T>Vector<T> Vector<T>::operator*(const Vector<T> &v) const throw(float)
{
    if(this->num != v.num)
		throw 'a';
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

template <typename T>T Vector<T>::dot(const Vector<T> &v) const throw(float)
{
    if(this->num != v.num)
		throw 'b';
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

template <typename T> void Vector<T>::Input()
{									// ���������и���ʵ��������������Զ���������չ����С��ά���Ĺ���
	const int N = 1;//1024;			// Nȡ��Сֵ1��Ϊ�˵��ԣ�ʵ��ʹ��ʱȡ1024
	T buffer[N];					// ����TYPE�������ݵĻ�������������N����
	int i, j, k;
	char ch;
	while(cin.get()!='(')			// ���˵�'('��֮ǰ�������ַ�
        ;
	while(true)						// ���˵���Բ����֮��Ŀհ��ַ�
	{
		ch = cin.peek();			// ͵����һ���ַ������Ƿ�Ϊ�հ��ַ�
		if(ch==' ' || ch=='\t' || ch=='\n' || ch=='\r')
			cin.get(ch);			// ���ǿհ��ַ�������˵�������ȡ���ã�
		else
			break;					// ֱ�������ǿհ��ַ���������whileѭ��
	}
	if(cin.peek()==')')				// ͵����һ���ַ�������')'
	{
	    cin.get(ch);
		this->resize(0);			// ������v��ά�����ó�0ά
		return;					    // �˳���������������Ϊ0ά����
	}
	for(k=0; ch!=')'; k++)
	{
		for(i=0; i<N&&ch!=')'; i++)	// ��ȡ��Ϊ����������TYPE�����ݣ����뻺����buffer�У���һ���ַ�ch��ʵΪ���ţ�
			cin >> buffer[i] >> ch; // ������buffer��(i<N)������')'�������ݵ������v����Դ��
		this->resize(k*N+i);		// ǰ���Ѿ���k�γ���������buffer��ÿ��N��TYPE�����ݣ��������ǵ�k+1�Σ���i��TYPE�����ݣ�
									// ��ע��reDim��������"����������ԭ������"�Ĺ���
		for(j=0; j<i; j++)
			(*this)[k*N+j] = buffer[j];	// ���������������صķ������������v[]��
	}
    return;                         // ���÷��ص�һ��ʵ�Σ���ʵ���������루�����������������͵ı��������������룩
}

template <typename T>void Vector<T>::Output() const
{
	if(this->num == 0)
		cout << "()";
	else
	{
		cout << '(' << this->p[0];
		for(int i=1; i<this->num; i++)
            {
                cout << ", " << this->p[i];
            }
                cout << ')';
	}
}

#endif // VECTOR_H
