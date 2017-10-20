#ifndef BASE_H
#define BASE_H
#include <iostream>
using namespace std;

template <typename T>
class Base
{
public:
	Base(int size=0, const T *x=NULL);			// ���캯������Ĭ�ϵĹ��캯����ת�����캯���ȣ�
	Base(const Base<T> &v);                     // ������캯��
    virtual ~Base();                              // ���麯�����鹹����
	Base & operator=(const Base<T> &v);         // �ֵ���������
        // �����Ƕ�����ܴ���Դʱ���Ĵ�ر�����

	int size() const;								// ��ȡ������ά��
	T & operator[](int index) const throw(char);    // ��Ʒ���������������±�Խ��ʱ�����쳣��Լ��Ϊ�ַ��ͣ�

	template <typename TYPE> friend ostream & operator<<(ostream &out,const Base<T> &B);
	//template <typename TYPE> friend istream & operator>>(istream &in, Base<TYPE> &v);

	bool operator==(const Base<T> &v) const;
	bool operator!=(const Base<T> &v) const;      // ����������ϵ�������һ��أ������������ܱȽϴ�С

	//virtual Base operator+(const Base<T> &v) const throw(int) = 0; // ���������޷���ӣ�ά����ͬ��ʱ�������쳣��Լ��Ϊ���ͣ�
	//virtual void Input(istream &in) = 0;
    virtual void Output() const = 0;
protected:
	int num;						// ������ά��
	T *p;							// ָ��������Դ�ռ���׵�ַ����ΪNULL
};
template <typename T> Base<T>::Base(int size, const T *x)
{
	if(size<=0)						// �����һ��ʵ��Ϊ0������������һ��0ά����
	{
		num = 0; p = NULL;
		return ;
	}
	p = new T[num=size];			// ��һ��ʵ�δ����㣬������ݳ�Աn��ֵ����������ڴ浥Ԫ
	if(p==NULL)						// �����벻�ɹ�������Ȼ����һ��0ά����
	{
		num = 0;
		return ;
	}
	for(int i=0; i<num; i++)		// ������ɹ������õڶ�������׼��������Ԫ��Ϊ�����ķ�����ֵ
		p[i] = (x!=NULL ? x[i] : 0);// ���ڶ�������Ϊ�յ�ַ��NULL��������һ��nά0����
}
template <typename T> T & Base<T>::operator[](int index) const throw(char)
{		// ���ڱ�������Ҫ���÷��� T ���͵ı��������±�Խ��ʱ�����۷���ʲô���ǲ��׵ģ��򵥴ֱ���exit(-1)Ҳ���ס�
	if(index<0 || index>=num)		// ����±�Խ��
		throw '\0';					// �����ַ����쳣����Լ����˵���������Ȼ�����ϼ����ţ������ñ����������д�������һ��׿Խ�����̿��Ʒ�����
	return p[index];				// ���÷��ص�index��������ʹ֮��Ϊ��ֵ
}
template <typename T> Base<T>::Base(const Base<T> &v) : num(0),p(NULL)
{
    //cout << "Base copy\n";
	*this = v;			// ֱ�ӵ��ø�ֵ���������.���ڸ�ֵ�������������delete[]���������ȱ�֤pΪNULL
}
template <typename T> Base<T>::~Base()
{
	if(p!=NULL) delete [] p;
	num = 0;			// һ����ԣ�����������ǲ���Ҫ�ġ����������������������������������������㲻��ȱ��
	p = NULL;
}
template <typename T> Base<T> & Base<T>::operator=(const Base<T> &v)
{
	if(&v == this) return *this;// �������Ҹ�ֵʱ�Ķ�������������Ǵ���������������ֱ���ͷű��������Դ��

	if(p!=NULL) delete [] p;	// �����ͷű�����ԭ�е���Դ
	if(v.num==0)				// �����ֵ����Ϊ0ά����
	{
		num = 0; p = NULL;		// �򽫱��������0ά������ע�⣺ԭ������Դ�Ѿ����ͷţ�
		return *this;			// ���ر�����
	}
	p = new T[num=v.num];		// ��ʱ����ֵ����һ������0ά����������ֵ�����ά����Ʊ������ά�����������ʵ��Ķ��ڴ浥Ԫ
	if(p==NULL)					// ������벻�ɹ�����ֻ�ܷ���0ά����
	{
		num = 0;
		return *this;
	}
	for(int i=0; i<num; i++)	// ��ֵ��ֵ��Դ
		p[i] = v.p[i];
	return *this;				// ���ر�������ʹ��ֵ���ʽ�Ľ��Ϊ��ֵ������
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
