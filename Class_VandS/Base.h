#ifndef BASE_H
#define BASE_H
#include <iostream>
using namespace std;

template <typename T>
class Base
{
public:
	Base(int size=0, const T *x=NULL);			// 构造函数（含默认的构造函数、转换构造函数等）
	Base(const Base<T> &v);                     // 深拷贝构造函数
    virtual ~Base();                              // （虚函数）虚构函数
	Base & operator=(const Base<T> &v);         // 深赋值运算符函数
        // 以上是对象可能带资源时的四大必备函数

	int size() const;								// 获取向量的维数
	T & operator[](int index) const throw(char);    // 设计方括号运算符，当下标越界时抛掷异常（约定为字符型）

	template <typename TYPE> friend ostream & operator<<(ostream &out,const Base<T> &B);
	//template <typename TYPE> friend istream & operator>>(istream &in, Base<TYPE> &v);

	bool operator==(const Base<T> &v) const;
	bool operator!=(const Base<T> &v) const;      // 重载两个关系运算符。一般地，两个向量不能比较大小

	//virtual Base operator+(const Base<T> &v) const throw(int) = 0; // 两个向量无法相加（维数不同）时，抛掷异常（约定为整型）
	//virtual void Input(istream &in) = 0;
    virtual void Output() const = 0;
protected:
	int num;						// 向量的维数
	T *p;							// 指向对象的资源空间的首地址，或为NULL
};
template <typename T> Base<T>::Base(int size, const T *x)
{
	if(size<=0)						// 如果第一个实参为0，或负数，则构造一个0维向量
	{
		num = 0; p = NULL;
		return ;
	}
	p = new T[num=size];			// 第一个实参大于零，则给数据成员n赋值，并申请堆内存单元
	if(p==NULL)						// 若申请不成功，则仍然构造一个0维向量
	{
		num = 0;
		return ;
	}
	for(int i=0; i<num; i++)		// 若申请成功，则用第二个参数准备的数组元素为向量的分量赋值
		p[i] = (x!=NULL ? x[i] : 0);// 若第二个参数为空地址（NULL），则构造一个n维0向量
}
template <typename T> T & Base<T>::operator[](int index) const throw(char)
{		// 由于本函数需要引用返回 T 类型的变量，当下标越界时，无论返回什么都是不妥的，简单粗暴地exit(-1)也不妥。
	if(index<0 || index>=num)		// 如果下标越界
		throw '\0';					// 抛掷字符型异常（按约定“说明情况”，然后交由上级部门，即调用本函数处另行处理。这是一种卓越的流程控制方法）
	return p[index];				// 引用返回第index个分量，使之可为左值
}
template <typename T> Base<T>::Base(const Base<T> &v) : num(0),p(NULL)
{
    //cout << "Base copy\n";
	*this = v;			// 直接调用赋值运算符函数.由于赋值运算符函数中有delete[]操作，须先保证p为NULL
}
template <typename T> Base<T>::~Base()
{
	if(p!=NULL) delete [] p;
	num = 0;			// 一般而言，下面的两行是不必要的。但是若程序中主动调用析构函数，这两个语句便不可缺少
	p = NULL;
}
template <typename T> Base<T> & Base<T>::operator=(const Base<T> &v)
{
	if(&v == this) return *this;// 避免自我赋值时的多余操作，甚至是错误操作（如下面的直接释放本对象的资源）

	if(p!=NULL) delete [] p;	// 主动释放本对象原有的资源
	if(v.num==0)				// 如果右值对象为0维向量
	{
		num = 0; p = NULL;		// 则将本对象处理成0维向量（注意：原来的资源已经被释放）
		return *this;			// 返回本对象
	}
	p = new T[num=v.num];		// 此时，右值对象一定不是0维向量。则按右值对象的维数设计本对象的维数，并申请适当的堆内存单元
	if(p==NULL)					// 如果申请不成功，则只能返回0维向量
	{
		num = 0;
		return *this;
	}
	for(int i=0; i<num; i++)	// 赋值右值资源
		p[i] = v.p[i];
	return *this;				// 返回本对象，以使赋值表达式的结果为左值对象本身
}
template <typename T> int Base<T>::size() const
{
	return num;
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

#endif // Base_H
