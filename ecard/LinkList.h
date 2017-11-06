// LinkList.h							本文件描述单向链表类模板。移植时，仅需要本文件
#ifndef LinkList_H
#define LinkList_H
#include <iostream>
using namespace std;

template <typename T> class LinkList;	// 提前声明

template <typename T> class Node		// 结点类
{
public:
	Node(const T &t=0) : data(t),n(m)		// 冒号语法初始化组合成员
	{
	    m++;
	}
	friend class LinkList<T>;			// 声明友元类
	friend class LFR;
private:
	T data;
	static int m;
	int n;
	Node *next;
};
template <typename T> int Node<T>::m=1;
template <typename T> class LinkList
{
protected:
	Node<T> *head, *cur_node;			// 链首指针、当前结点指针
	int num;							// 链表中的结点数
public:
	LinkList();							// 默认的构造函数
	LinkList(const T *t, int n);		// 利用连续元素创建链表
	LinkList(const LinkList &list);		// 拷贝构造链表
	LinkList & operator=(const LinkList &list);		// 赋值运算
	virtual ~LinkList();				// 析构函数（虚函数）
	Node<T> *GoTop();					// 绝对位置：首结点
	Node<T> *Go(int n);					// 绝对位置：第 n （从 0 起）个结点
	Node<T> *GoBottom();				// 绝对位置：尾结点
	Node<T> *Skip(int n=1);				// 相对定位：偏移 n (可为负数)个结点
	bool isEmpty() const;				// 当前链表是否为空链表
	bool isBegin() const;				// 当前结点是否为首结点
	bool isLast() const;				// 当前结点是否为尾结点
	Node<T> *CurNode() const;			// 返回当前结点的地址
	T  & CurData() const;				// 引用返回当前结点本身
	int  CurPos() const;				// 返回当前结点序号。0 为首结点，-1 无当前结点
	int  NumNodes() const;				// 返回当前链表结点数
	void InsBeforeHeadNode(const T &t);	// 链首结点前，成为新链首
	void DeleteCurNode();				// 当前结点
	void FreeList();					// 释放所有结点
	void ShowCurData() const;			// 输出当前结点数据
	void ShowList(int LinePerNode=0) const;			// 输出所有结点数据
	void Reverse();						// 结点顺序倒置
};

template <typename T>
LinkList<T>::LinkList()
{
	num = 0;
	head = cur_node = NULL;
}

template <typename T>
LinkList<T>::LinkList(const T*t,int n)
{
	Node<T> *p;
	head = NULL;
	for(int i=n-1; i>=0; i--)
	{
		p = new Node<T>(t[i]);
		p->next = head;
		head = p;
	}
	num = n;
	cur_node = head;
}

template <typename T>
LinkList<T>::LinkList(const LinkList<T> &list)
{
	Node<T> *p, *pTail, *temp=list.head;
	if((num=list.num)==0)
	{
		head = cur_node = NULL;
		return;
	}
	head = pTail = new Node<T>(list.head->data);
	if(list.head == list.cur_node) cur_node = head;
	for(int i=1; i<num; i++)
	{
		temp = temp->next;
		p = new Node<T>(temp->data);
		if(temp == list.cur_node) cur_node = p;
		pTail->next = p;
		pTail = p;
	}
	pTail->next = NULL;
}

template <typename T>
LinkList<T> & LinkList<T>::operator=(const LinkList<T> &list)
{
	if(list.head==this->head) return *this;
	FreeList();
	Node<T> *p, *pTail, *temp=list.head;
	if((num=list.num) == 0)
	{
		head = cur_node = NULL;
		return *this;
	}
	head = pTail = new Node<T>(list.head->data);
	if(list.head == list.cur_node) cur_node = head;
	for(int i=1; i<num; i++)
	{
		temp = temp->next;
		p = new Node<T>(temp->data);
		if(temp == list.cur_node) cur_node = p;
		pTail->next = p;
		pTail = p;
	}
	pTail->next = NULL;
	return *this;
}

template <typename T>
LinkList<T>::~LinkList<T>()
{
	FreeList();

}

template <typename T>
Node<T> *LinkList<T>::GoTop()
{
	return cur_node = head;
}

template <typename T>
Node<T> *LinkList<T>::Go(int n)
{
	if((cur_node=head) == NULL) return cur_node;
	for(int i=0; i<n && cur_node!=NULL; i++)
		cur_node = cur_node->next;
	return cur_node;
}

template <typename T> Node<T> *LinkList<T>::GoBottom()
{
	if((cur_node=head) == NULL) return cur_node;
	while(cur_node->next!=NULL)
		cur_node = cur_node->next;
	return cur_node;
}

template <typename T> Node<T> *LinkList<T>::Skip(int n)
{
	int i;
	if(n > 0)
	{
		for(i=0; i<n && cur_node!=NULL; i++)
			cur_node = cur_node->next;
	}
	else if(n < 0)
	{
		int m = CurPos() + n;
		cur_node = (m < 0) ? NULL : Go(m);
	}
	return cur_node;
}

template <typename T> bool LinkList<T>::isEmpty() const
{
	return head==NULL;
}

template <typename T> bool LinkList<T>::isBegin() const
{
	return cur_node==head;
}

template <typename T> bool LinkList<T>::isLast() const
{
	return cur_node->next==NULL;
}

template <typename T> Node<T> *LinkList<T>::CurNode() const
{
	return cur_node;
}

template <typename T> T & LinkList<T>::CurData() const
{
	return cur_node->data;
}

template <typename T> int LinkList<T>::CurPos() const
{
	if(cur_node==NULL) return -1;
	for(Node<T> *p = head; p!=NULL; p=p->next)
	{
		if(p == cur_node)
			return p.n;
	}
	return -1;
}

template <typename T> int LinkList<T>::NumNodes() const
{
	return num;
}

template <typename T>
void LinkList<T>::InsBeforeHeadNode(const T &t)
{
	num++;
	Node<T> *p = new Node<T>(t);
	p->next = head;
	head = p;
	cur_node = head;
}

template <typename T> void LinkList<T>::DeleteCurNode()
{
	if(cur_node==NULL) return;
	if(cur_node==head)
	{
		num--;
		head = head->next;
		delete cur_node;
		cur_node = head;
		return;
	}
	Node<T> *pGuard = head;
	while(pGuard->next!=NULL && pGuard->next!=cur_node)
		pGuard = pGuard->next;
	if(pGuard->next != NULL)
	{
		num--;
		pGuard->next = cur_node->next;
		delete cur_node;
		cur_node = pGuard->next;
	}
}

template <typename T> void LinkList<T>::FreeList()
{
	Node<T> *p;
	while(head!=NULL)
	{
		p = head;
		head = head->next;
		delete p;
	}
	cur_node = NULL;
	num = 0;
}


template <typename T> void LinkList<T>::ShowCurData() const
{
	if(cur_node!=NULL)
		cout << cur_node->data;
}

template <typename T>
void LinkList<T>::ShowList(int LinePerNode) const
{
	if(LinePerNode==0) cout << "head";
	for(Node<T> *p=head; p!=NULL; p=p->next)
	{
		if(LinePerNode==0)
			cout << (p==cur_node ? " ★ " : " → ")
				 << p->data;
		else
			cout << (p==cur_node ? "★" : "  ")
				 << p->data << endl;
	}
	if(LinePerNode==0) cout << " → NULL" << endl;
}

template <typename T> void LinkList<T>::Reverse()
{
	if(head==NULL) return;
	Node<T> *p, *rest;
	// 首先将原链表拆成两条链表
	rest = head->next;          // 旧链：原第一个结点起
	head->next = NULL;			// 新链：单结点链表，原第 0 个结点
    // 依次处理，直至旧链为空
	while(rest != NULL)
	{
		p = rest;
		rest = rest->next;		// 卸下旧链“首”结点
		p->next = head;
		head = p;				// 装在新链首结点前
	}
}


#endif
