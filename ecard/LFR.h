#ifndef LFR_H
#define LFR_H
#include "eCard.h"
#include "LinkList.h"
#include <string>
#include<cstdlib>
#include <iomanip>
using namespace std;
class LFR :public LinkList<record>      //LFR=LinkList for Record
{
public:
    LFR(string Name="",string id="",const record *t=NULL,int n=0):LinkList(t,n),name(Name),ID(id) //���캯��
    {
        sum=0;
        for(int i=0;i<n;++i)
        {
            sum+=t[i].expense;
        }
    }
    LFR(const LFR &list):LinkList(list),name(list.name),ID(list.ID)
    {
        sum=RecountSum();
    }
    virtual ~LFR();
    LFR & operator=(const LFR &list);
    double Sum() const;
    string Name() const;
    string Id() const;
    void InsBeforeHeadNode(const record &t);//���ز���ͷ�ڵ�
    void DeleteCurNode();                   //����ɾ����ǰ���
    void FreeList();                        //�����ͷ�����
    void ShowList()const;                   //�������
    void Find(const string &a,const string &b);//Ѱ�ҵ�ʱ�䷶ΧΪa~b�����Ѽ�¼�����
    double RecountSum();                    //���¸��ݽ�����ݼ������

private:
    double sum;//���
    string name;//��������
    string ID;//����ѧ��
};


LFR & LFR::operator=(const LFR &list)
{
    if(list.head==this->head) return *this;
    FreeList();
    Node<record> *p, *p2, *pl=list.head;
    num=list.num;
    if(num == 0)
    {
        head = NULL;
		cur_node=NULL;
        return *this;
    }
    p2 = new Node<record>(list.head->data);
	head=p2;
    if(list.head == list.cur_node) cur_node = head;
    for(int i=1; i<num; i++)
    {
        pl = pl->next;
        p = new Node<record>(pl->data);
        if(pl == list.cur_node) cur_node = p;
        p2->next = p;
        p2 = p;
    }
    p2->next = NULL;
    sum=RecountSum();
    name=list.name;
    ID=list.ID;
    return *this;
}

LFR::~LFR()
{
    FreeList();
}

void LFR::FreeList()
{
    sum=0;
    name="";
    ID="";
}

double LFR::Sum() const
{
    return sum;
}

string LFR::Name() const
{
    return name;
}

string LFR::Id() const
{
    return ID;
}

void LFR::InsBeforeHeadNode(const record &t)
{
    num++;
    sum+=t.expense;
    Node<record> *p = new Node<record>(t);
    p->next = head;
    head = p;
    cur_node = head;
}

void LFR::DeleteCurNode()
{
    if(cur_node==NULL) return;
    if(cur_node==head)
    {
        num--;
        sum-=(cur_node->data).expense;
        head = head->next;
        delete cur_node;
        cur_node = head;
        return;
    }
    //����ǰ����ǰһ�����
    Node<record> *p = head;
    while(p->next!=NULL && p->next!=cur_node)
        p = p->next;
    if(p->next != NULL)
    {
        num--;
        sum-=p->next->data.expense;
        p->next = cur_node->next;
        delete cur_node;
        cur_node = p->next;
    }
}

double LFR::RecountSum()
{
    sum=0;
    cur_node=head;
    for(int i=0;i<num;++i)
    {
        sum+=((cur_node->data).expense);
        cur_node=cur_node->next;
    }
    return sum;
}

void LFR::Find(const string &a,const string &b)
{
    int _min=atoi(a.c_str());
    int _max=atoi(b.c_str());
    if(_min>_max)
    {
        int temp=_min;_min=_max;_max=temp;
    }
    cout<<setfill(' ')<<setw(10)<<"����"<<setw(10)<<"ʱ��"<<setw(10)<<"����"<<endl;
    bool isFind=false;
    for(cur_node=head;cur_node!=NULL;cur_node=cur_node->next)
    {
        if(_min<=atoi(cur_node->data.date.c_str())&&_max>=atoi(cur_node->data.date.c_str()))
        {
            isFind=true;
            cout<<setw(10)<<cur_node->data.date<<setw(10)<<cur_node->data.time<<setw(10)<<cur_node->data.expense<<endl;
        }
    }
    if(!isFind) cout<<"δ��ѯ����ؼ�¼��"<<endl;
}

void LFR::ShowList()const
{
    cout<<"�����"<<sum<<endl;
    cout<<"��ϸ������Ϣ���£�"<<endl;
    cout<<setfill(' ')<<setw(10)<<"����"<<setw(10)<<"ʱ��"<<setw(10)<<"����"<<endl;
    for(Node<record> *p=head; p!=NULL; p=p->next)
	{
		cout<<setw(10)<<p->data.date<<setw(10)<<p->data.time<<setw(10)<<p->data.expense<<endl;
	}
}

#endif // LFR_H
