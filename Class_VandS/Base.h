#ifndef BASE_H
#define BASE_H
#include <iostream>
using namespace std;

template <typename T>
class Base
{
public:
	Base(int size=0, const T *x=NULL);			//构造函数
	Base(const Base<T> &v);                     //拷贝构造函数
    virtual ~Base();                            //虚析构函数
    Base & operator=(const Base<T> &v);         //深赋值运算符重载

	int size() const;							//获取维数
    bool empty() const;                         //判断是否为空

	T & operator[](int index) const throw(char);//方括号运算符，当下标越界时抛掷异常
	bool operator==(const Base<T> &v) const;
	bool operator!=(const Base<T> &v) const;

	virtual void Input() =0;                    //输入函数，向量与字符串处理方式不同
    virtual void Output() const = 0;            //输出函数，向量与字符串处理方式不同
    template <typename TYPE> friend ostream & operator<<(ostream &out,const Base<T> &B);
	template <typename TYPE> friend istream & operator>>(istream &in,Base<T> &B);
protected:
	int num;						// 维数
	T *p;							// 指向对象的资源空间的首地址
};

template <typename T> Base<T>::Base(int size, const T *x)
{
	if(size<=0)
	{
		num = 0; p = NULL;
		return ;
	}
	p = new T[num=size];
	if(p==NULL)						//申请失败
	{
		num = 0;
		return ;
	}
	for(int i=0; i<num; i++)		// 若申请成功，则用第二个参数准备的数组元素为向量（字符串）赋值
		p[i] = (x!=NULL ? x[i] : 0);// 若第二个参数为空地址（NULL），则构造一个n维0向量（字符串）
}

template <typename T> Base<T>::Base(const Base<T> &v) : num(0),p(NULL)
{
	*this = v;			            //直接调用赋值运算符函数.由于赋值运算符函数中有delete[]操作，须先保证p为NULL
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
	if(p!=NULL) delete [] p;	    //释放原有的资源
	if(v.num==0)
	{
		num = 0; p = NULL;
		return *this;
	}
	p = new T[num=v.num];
	if(p==NULL)					   //申请不成功，返回0维向量
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
