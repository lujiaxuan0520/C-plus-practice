// LinkList.h
#ifndef LinkList_H
#define LinkList_H
#include <iostream>
using namespace std;

template <typename T> class LinkList;

template <typename T> class Node
{
public:
	Node(const T &t=0) : data(t)
	{
	}
	friend class LinkList<T>;
	friend class LFR;
private:
	T data;
	Node *next;
};
template <typename T> class LinkList
{
public:
	LinkList();
	LinkList(const T *t, int n);
	LinkList(const LinkList &list);
	LinkList & operator=(const LinkList &list);
	virtual ~LinkList();
	Node<T> *GoTop();					// 当前指针指向首结点
	Node<T> *Go(int n);					// 当前指针指向第n个结点
	Node<T> *GoBottom();				// 当前指针指向尾结点
	Node<T> *Skip(int n=1);				// 当前指针移动n个结点
	bool isEmpty() const;
	bool isBegin() const;				// 当前结点是否为首结点
	bool isLast() const;				// 当前结点是否为尾结点
	Node<T> *CurNode() const;			// 返回当前结点的地址
	int  CurPos() const;				// 返回当前结点的序号。
	int  NumNodes() const;				// 返回当前链表的结点数
	void InsBeforeHeadNode(const T &t);	// 在链首插入新的结点
	void DeleteCurNode();
	void FreeList();
protected:
	Node<T> *head, *cur_node;
	int num;//结点总数
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
	for(int i=n-1; i>=0; --i)
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
    head=cur_node=NULL;
    num=0;
    *this=list;   //此处调用了赋值运算符
}

template <typename T>
LinkList<T> & LinkList<T>::operator=(const LinkList<T> &list)
{
	if(list.head==this->head) return *this;
	FreeList();
	Node<T> *p, *p2, *pl=list.head;
	num=list.num;
	if(num==0)
	{
		head = NULL;
		cur_node=NULL;
		return *this;
	}
	p2 = new Node<T>(list.head->data);
	head=p2;
	if(list.head == list.cur_node) cur_node = head;
	for(int i=1; i<num; i++)
	{
		pl = pl->next;
		p = new Node<T>(pl->data);
		if(pl == list.cur_node) cur_node = p;
		p2->next = p;
		p2 = p;
	}
	p2->next = NULL;
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
	cur_node=head;
	return cur_node;
}

template <typename T>
Node<T> *LinkList<T>::Go(int n)
{
	cur_node=head;
	for(int i=0; i<n && cur_node!=NULL; ++i)
		cur_node = cur_node->next;
	return cur_node;
}

template <typename T> Node<T> *LinkList<T>::GoBottom()
{
	if(head == NULL) return head;
	cur_node=head;
	while(cur_node->next!=NULL)
		cur_node = cur_node->next;
	return cur_node;
}

template <typename T> Node<T> *LinkList<T>::Skip(int n)
{
	if(n>0)
	{
		for(int i=0;i<n&&cur_node!=NULL;++i)
			cur_node=cur_node->next;
	}
	else if(n<0)
	{
		int m=CurPos()+n;
		if(m<0) cur_node=NULL;
		else
        {
            cur_node=Go(m);
        }
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

template <typename T> int LinkList<T>::CurPos() const
{
	if(cur_node==NULL) return -1;
	int n = 0;
	for(Node<T> *p = head; p!=NULL; p=p->next)
	{
		if(p == cur_node)
			return n;
		n++;
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
	Node<T> *p = new Node<T>(t);
	p->next = head;
	head = p;
	cur_node = head;
	num++;
}

template <typename T> void LinkList<T>::DeleteCurNode()
{
	if(cur_node==NULL) return;
	if(cur_node==head)
	{
		head = head->next;
		delete cur_node;
		cur_node = head;
		num--;
		return;
	}
	//捕获当前结点的前一个结点
	Node<T> *p = head;
	while(p->next!=NULL && p->next!=cur_node)
		p = p->next;
	if(p->next != NULL)
	{
		p->next = cur_node->next;
		delete cur_node;
		cur_node = p->next;
		num--;
	}
}

template <typename T> void LinkList<T>::FreeList()
{
	Node<T> *p=NULL;
	while(head!=NULL)
	{
		p = head;
		head = head->next;
		delete p;
	}
	cur_node = NULL;
	num = 0;
}

#endif
