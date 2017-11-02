#include"LinkList.h"

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
	cout << "析构一条链表。" << endl;
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

template <typename T> template <typename T1> Node<T> *
LinkList<T>::Locate(const T1 &t, bool restart)
{
	static Node<T> *p = head;		// 局部静态指针变量

	if(head==NULL) return cur_node=NULL;
	if(restart) p = head;
	while(p!=NULL && T1(p->data) != t)
		p = p->next;
	cur_node = p;
	if(p!=NULL) p = p->next;
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
	num++;
	Node<T> *p = new Node<T>(t);
	p->next = head;
	head = p;
	cur_node = head;
}

//template <typename T>
//void LinkList<T>::InsBeforeCurNode(const T &t)
//{
//	Skip(-1);
//	if(cur_node==NULL)
//		InsBeforeHeadNode(t);
//	else
//		InsAfterCurNode(t);
//}
//
//template <typename T>
//void LinkList<T>::InsAfterCurNode(const T &t)
//{
//	if(cur_node==NULL)
//		Append(t);
//	else
//	{
//		num++;
//		Node<T> *p = new Node<T>(t);
//		p->next = cur_node->next;
//		cur_node->next = p;
//		cur_node = p;
//	}
//}
//
//template <typename T> void LinkList<T>::Append(const T &t)
//{
//	Node<T> *p = head;
//	num++;
//	if(head==NULL)
//		head = p = new Node<T>(t);
//	else
//	{
//		while(p->next != NULL)
//			p = p->next;
//		p->next = new Node<T>(t);
//		p = p->next;
//	}
//	p->next = NULL;
//	cur_node = p;
//
//}

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

//template <typename T> void LinkList<T>::Change(const T &t)
//{
//	if(cur_node!=NULL)
//		cur_node->data = t;
//}

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
//
//template <typename T> template <typename T1>
//void LinkList<T>::Sort(const T1 &t, bool ascending)
//{
//	if(head==NULL) return;
//	Node<T> *p, *pGuard, *rest;
//	// 首先将原链表拆成两条链表
//	rest = head->next;			// 旧链：原第一个结点起
//	head->next = NULL;			// 新链：单结点链表，原第 0 个结点
//    // 依次处理，直至旧链为空
//	while(rest != NULL)
//	{
//	  p = rest;
//	  rest = rest->next;		// 卸下旧链“首”结点
//	  if(ascending && (T1)p->data < (T1)head->data
//		   || !ascending && T1(p->data) > T1(head->data))
//	  {
//		  p->next = head;
//		  head = p;
//		  continue;
//	  }
//	  pGuard = head;
//	  while(pGuard->next!=NULL &&
//		(ascending && T1(pGuard->next->data) <= T1(p->data) ||
//		!ascending && T1(pGuard->next->data) >= T1(p->data)) )
//		  pGuard = pGuard->next;
//	  p->next = pGuard->next;
//	  pGuard->next = p;
//	}
//}

//template <typename T> template <typename T1>
//void LinkList<T>::Merge(LinkList &linkA,
//			LinkList &linkB, const T1 &t, bool ascending)
//{
//  if(linkA.head==NULL)
//  {
//	  linkA.head = linkB.head;
//	  linkB.head = NULL;
//	  return ;
//  }
//  if(linkB.head==NULL) return;
//
//  Node<T> *pA, *pB, *p, *pEnd;
//  if(ascending&&T1(linkA.head->data)<=T1(linkB.head->data)
//	|| !ascending&&T1(linkA.head->data)>=T1(linkB.head->data))
//  {
//	  pA = linkA.head->next;
//	  pB = linkB.head;
//  }
//  else
//  {
//	  pA = linkA.head;
//	  pB = linkB.head->next;
//	  linkA.head = linkB.head;
//  }
//  pEnd = linkA.head;
//  linkA.head->next = NULL;
//  linkB.head = NULL;
//
//  while(pA!=NULL && pB!=NULL)
//  {
//	  if(ascending && T1(pA->data) <= T1(pB->data)
//		   || !ascending && T1(pA->data) >= T1(pB->data) )
//	  {
//		  p = pA;
//		  pA = pA->next;
//	  }
//	  else
//	  {
//		  p = pB;
//		  pB = pB->next;
//	  }
//	  pEnd->next = p;
//	  pEnd = p;
//  }
//  if(pA == NULL)
//	  pEnd->next = pB;
//  else
//	  pEnd->next = pA;
//}

template <typename T>
void LinkList<T>::Save(const char *filename,
					   ios_base::openmode OpenMode)
{
	ofstream outfile(filename, OpenMode);
	Node<T> *p;
	for(p=head; p!=NULL; p=p->next)
		outfile << p->data << endl;
	outfile.close();
}

template <typename T>
void LinkList<T>::Load(const char *filename,
                       ios_base::openmode OpenMode)
{
	ifstream infile(filename, OpenMode);
	T x;
	while(infile >> x)
		Append(x);
	infile.close();
}
