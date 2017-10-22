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
//    Vector & operator=(const Vector<T> &v);   //感觉赋值运算符可以继承
    Vector operator+(const Vector<T> &v) const throw(int);  //向量相加，与字符串的处理方法不同
    Vector & operator+=(const Vector<T> &v);
    Vector operator*(int n) const;                          //向量数乘
    Vector operator*(const Vector<T> &v) const throw(float);//向量每一位对应元素相乘所形成的向量
    Vector &operator*=(int n);
    Vector &operator*=(const Vector<T> &v);                 //因为调用*不再抛掷异常
    T dot(const Vector<T> &v) const throw(float);           //向量数量积
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
//    if(&v == this) return *this;// 避免自我赋值时的多余操作，甚至是错误操作（如下面的直接释放本对象的资源）
//	if(this->p!=NULL)
//        delete [] this->p;	// 主动释放本对象原有的资源
//	if(v.num==0)				// 如果右值对象为0维向量
//	{
//		this->num = 0; this->p = NULL;		// 则将本对象处理成0维向量（注意：原来的资源已经被释放）
//		return *this;			// 返回本对象
//	}
//	this->p = new T[this->num=v.num];		// 此时，右值对象一定不是0维向量。则按右值对象的维数设计本对象的维数，并申请适当的堆内存单元
//	if(this->p==NULL)					// 如果申请不成功，则只能返回0维向量
//	{
//		this->num = 0;
//		return *this;
//	}
//	for(int i=0; i<this->num; i++)	// 赋值右值资源
//		this->p[i] = v.p[i];
//	return *this;				// 返回本对象，以使赋值表达式的结果为左值对象本身
//}

template <typename T> Vector<T> Vector<T>::operator+(const Vector<T> &v) const throw(int)
{
	if(this->num != v.num)				// 维数不同，无法相加。将抛掷一个整型异常
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
	if(size <0 || size == this->num)			// 维数不变，直接返回本对象
		return *this;
	Vector<T> temp(size);
	for(int i=0; i<temp.num; i++)
		temp.p[i] = (i<this->num)? this->p[i] : 0;
	return *this=temp;
}

template <typename T> void Vector<T>::Input()
{									// 本函数具有根据实际输入的向量，自动调整（扩展或缩小）维数的功能
	const int N = 1;//1024;			// N取最小值1是为了调试，实际使用时取1024
	T buffer[N];					// 接收TYPE类型数据的缓冲区，容量由N决定
	int i, j, k;
	char ch;
	while(cin.get()!='(')			// 过滤掉'('及之前的所有字符
        ;
	while(true)						// 过滤掉左圆括号之后的空白字符
	{
		ch = cin.peek();			// 偷看下一个字符，看是否为空白字符
		if(ch==' ' || ch=='\t' || ch=='\n' || ch=='\r')
			cin.get(ch);			// 若是空白字符，则过滤掉（即读取后不用）
		else
			break;					// 直到遇到非空白字符，结束本while循环
	}
	if(cin.peek()==')')				// 偷看下一个字符，若是')'
	{
	    cin.get(ch);
		this->resize(0);			// 将对象v的维数设置成0维
		return;					    // 退出本函数，即输入为0维向量
	}
	for(k=0; ch!=')'; k++)
	{
		for(i=0; i<N&&ch!=')'; i++)	// 读取作为向量分量的TYPE型数据（放入缓冲区buffer中）及一个字符ch（实为逗号）
			cin >> buffer[i] >> ch; // 缓冲区buffer满(i<N)或遇到')'，则将数据导入对象v的资源中
		this->resize(k*N+i);		// 前面已经有k次充满缓冲区buffer（每次N个TYPE型数据），现在是第k+1次（有i个TYPE型数据）
									// 请注意reDim函数具有"尽量保留了原有数据"的功能
		for(j=0; j<i; j++)
			(*this)[k*N+j] = buffer[j];	// 利用了向量类重载的方括号运算符（v[]）
	}
    return;                         // 引用返回第一个实参，以实现连续输入（亦能与其他数据类型的变量依次连续输入）
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
