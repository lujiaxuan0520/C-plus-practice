// LinkList.h							���ļ���������������ģ�塣��ֲʱ������Ҫ���ļ�
#ifndef LinkList_H
#define LinkList_H
#include <iostream>
using namespace std;

template <typename T> class LinkList;	// ��ǰ����

template <typename T> class Node		// �����
{
public:
	Node(const T &t=0) : data(t),n(m)		// ð���﷨��ʼ����ϳ�Ա
	{
	    m++;
	}
	friend class LinkList<T>;			// ������Ԫ��
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
	Node<T> *head, *cur_node;			// ����ָ�롢��ǰ���ָ��
	int num;							// �����еĽ����
public:
	LinkList();							// Ĭ�ϵĹ��캯��
	LinkList(const T *t, int n);		// ��������Ԫ�ش�������
	LinkList(const LinkList &list);		// ������������
	LinkList & operator=(const LinkList &list);		// ��ֵ����
	virtual ~LinkList();				// �����������麯����
	Node<T> *GoTop();					// ����λ�ã��׽��
	Node<T> *Go(int n);					// ����λ�ã��� n ���� 0 �𣩸����
	Node<T> *GoBottom();				// ����λ�ã�β���
	Node<T> *Skip(int n=1);				// ��Զ�λ��ƫ�� n (��Ϊ����)�����
	bool isEmpty() const;				// ��ǰ�����Ƿ�Ϊ������
	bool isBegin() const;				// ��ǰ����Ƿ�Ϊ�׽��
	bool isLast() const;				// ��ǰ����Ƿ�Ϊβ���
	Node<T> *CurNode() const;			// ���ص�ǰ���ĵ�ַ
	T  & CurData() const;				// ���÷��ص�ǰ��㱾��
	int  CurPos() const;				// ���ص�ǰ�����š�0 Ϊ�׽�㣬-1 �޵�ǰ���
	int  NumNodes() const;				// ���ص�ǰ��������
	void InsBeforeHeadNode(const T &t);	// ���׽��ǰ����Ϊ������
	void DeleteCurNode();				// ��ǰ���
	void FreeList();					// �ͷ����н��
	void ShowCurData() const;			// �����ǰ�������
	void ShowList(int LinePerNode=0) const;			// ������н������
	void Reverse();						// ���˳����
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
			cout << (p==cur_node ? " �� " : " �� ")
				 << p->data;
		else
			cout << (p==cur_node ? "��" : "  ")
				 << p->data << endl;
	}
	if(LinePerNode==0) cout << " �� NULL" << endl;
}

template <typename T> void LinkList<T>::Reverse()
{
	if(head==NULL) return;
	Node<T> *p, *rest;
	// ���Ƚ�ԭ��������������
	rest = head->next;          // ������ԭ��һ�������
	head->next = NULL;			// ���������������ԭ�� 0 �����
    // ���δ���ֱ������Ϊ��
	while(rest != NULL)
	{
		p = rest;
		rest = rest->next;		// ж�¾������ס����
		p->next = head;
		head = p;				// װ�������׽��ǰ
	}
}


#endif
