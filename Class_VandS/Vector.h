#ifndef VECTOR_H
#define VECTOR_H
#include"Base.h"
#include<cmath>
template <typename T>
class Vector:public Base<T>
{
public:
    Vector(int size=0,const T *x=NULL):Base<T>(size,x){}    
    Vector operator+(const Vector<T> &v) const throw(double);//向量相加，与字符串的处理方法不同
    Vector & operator+=(const Vector<T> &v);
    Vector operator*(int n) const;                           //向量数乘
    Vector operator*(const Vector<T> &v) const throw(double);//向量每一位对应元素相乘所形成的向量
    Vector &operator*=(int n);
    Vector &operator*=(const Vector<T> &v);                  //因为调用*不再抛掷异常
    T mol() const;                                           //向量的模
    T dot(const Vector<T> &v) const throw(double);           //向量数量积
    Vector & resize(int size);
    void Input(istream& in);
    void Output(ostream& out)const;
    void f(){cout<<"Vector::f()"<<endl;}
};

template <typename T> Vector<T> Vector<T>::operator+(const Vector<T> &v) const throw(double)
{
	if(this->num != v.num)				// 维数不同，无法相加。将抛掷一个异常
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
	if(size <0 || size == this->num)			// 维数不变，直接返回本对象
		return *this;
	Vector<T> temp(size);
	for(int i=0; i<temp.num; i++)
		temp.p[i] = (i<this->num)? this->p[i] : 0;
	return *this=temp;
}

template <typename T> void Vector<T>::Input(istream& in)
{									// 本函数具有根据实际输入的向量，自动调整（扩展或缩小）维数的功能
	const int N = 1;//1024;			// N取最小值1是为了调试，实际使用时取1024
	T buffer[N];					// 接收TYPE类型数据的缓冲区，容量由N决定
	int i, j, k;
	char ch;
	while(in.get()!='(')			// 过滤掉'('及之前的所有字符
        ;
	while(true)						// 过滤掉左圆括号之后的空白字符
	{
		ch = in.peek();			// 偷看下一个字符，看是否为空白字符
		if(ch==' ' || ch=='\t' || ch=='\n' || ch=='\r')
			in.get(ch);			// 若是空白字符，则过滤掉（即读取后不用）
		else
			break;					// 直到遇到非空白字符，结束本while循环
	}
	if(in.peek()==')')				// 偷看下一个字符，若是')'
	{
	    in.get(ch);
		this->resize(0);			// 将对象v的维数设置成0维
		return;					    // 退出本函数，即输入为0维向量
	}
	for(k=0; ch!=')'; k++)
	{
		for(i=0; i<N&&ch!=')'; i++)	// 读取作为向量分量的TYPE型数据（放入缓冲区buffer中）及一个字符ch（实为逗号）
			in >> buffer[i] >> ch; // 缓冲区buffer满(i<N)或遇到')'，则将数据导入对象v的资源中
		this->resize(k*N+i);		// 前面已经有k次充满缓冲区buffer（每次N个TYPE型数据），现在是第k+1次（有i个TYPE型数据）
									// 请注意reDim函数具有"尽量保留了原有数据"的功能
		for(j=0; j<i; j++)
			(*this)[k*N+j] = buffer[j];	// 利用了向量类重载的方括号运算符（v[]）
	}
    return;                         // 引用返回第一个实参，以实现连续输入（亦能与其他数据类型的变量依次连续输入）
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
