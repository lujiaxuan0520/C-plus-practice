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
    if(&v == this) return *this;// 避免自我赋值时的多余操作，甚至是错误操作（如下面的直接释放本对象的资源）
	if(this->p!=NULL)
        delete [] this->p;	// 主动释放本对象原有的资源
	if(v.num==0)				// 如果右值对象为0维向量
	{
		this->num = 0; this->p = NULL;		// 则将本对象处理成0维向量（注意：原来的资源已经被释放）
		return *this;			// 返回本对象
	}
	this->p = new T[this->num=v.num];		// 此时，右值对象一定不是0维向量。则按右值对象的维数设计本对象的维数，并申请适当的堆内存单元
	if(this->p==NULL)					// 如果申请不成功，则只能返回0维向量
	{
		this->num = 0;
		return *this;
	}
	for(int i=0; i<this->num; i++)	// 赋值右值资源
		this->p[i] = v.p[i];
	return *this;				// 返回本对象，以使赋值表达式的结果为左值对象本身
}
template <typename T> Vector<T> Vector<T>::operator+(const Vector<T> &v) const throw(int)
{
	if(this->num != v.num)				// 维数不同，无法相加。将抛掷一个整型异常
		throw 1;
	Vector<T> temp(*this);
	for(int i=0; i<this->num; i++)
		temp.p[i] += v.p[i];
	return temp;					// 不能改变两个操作数，只能值返回对象
}
template <typename T> Vector<T> & Vector<T>::resize(int size)
{
	if(size <0 || size == this->num)			// 维数不变，直接返回本对象
		return *this;
	Vector<T> temp(size);
	for(int i=0; i<temp.num; i++)		// 维数可能变大或变小
		temp.p[i] = (i<this->num)? this->p[i] : 0;	// 尽量保留原有数据，
	return *this=temp;					// 利用（深）赋值运算符函数
}
template <typename T>void Vector<T>::Output() const
{
	if(this->num == 0)
		cout << "()";				// 若v为0维向量，则仅输出一对圆括号
	else
	{
		cout << '(' << this->p[0];		// 否则，维数大于或等于1，那么，可先输出左括号和第一个分量
		for(int i=1; i<this->num; i++)	// 注意循环控制变量i从1起
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
