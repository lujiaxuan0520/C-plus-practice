#ifndef LFR_H
#define LFR_H
#include "eCard.h"
#include "LinkList.h"
#include <string>
#include<cstdlib>
#include <iomanip>
using namespace std;
class LFR :public LinkList<record>
{
public:
    LFR(string Name="",string id="",const record *t=NULL,int n=0):LinkList(t,n),name(Name),ID(id)
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
    double Sum();
    double CurNodeExpense();
    string Name();
    string Id();
    void InsBeforeHeadNode(const record &t);
    void DeleteCurNode();
    void FreeList();
    void ShowList()const;
    void Find(const string &a,const string &b);
    double RecountSum();
private:
    double sum;//余额
    string name;//对象姓名
    string ID;//对象学号
};


LFR & LFR::operator=(const LFR &list)
{
    if(list.head==this->head) return *this;
    FreeList();
    Node<record> *p, *pTail, *temp=list.head;
    if((num=list.num) == 0)
    {
        head = cur_node = NULL;
        return *this;
    }
    head = pTail = new Node<record>(list.head->data);
    if(list.head == list.cur_node) cur_node = head;
    for(int i=1; i<num; i++)
    {
        temp = temp->next;
        p = new Node<record>(temp->data);
        if(temp == list.cur_node) cur_node = p;
        pTail->next = p;
        pTail = p;
    }
    pTail->next = NULL;
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

double LFR::Sum()
{
    return sum;
}

double LFR::CurNodeExpense()
{
    return cur_node->data.expense;
}

string LFR::Name()
{
    return name;
}

string LFR::Id()
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
    cur_node=head;
    Node<record> *p1=NULL;
    if(_max>=atoi(cur_node->data.date.c_str()))
    {
            p1=cur_node;
    }
    for(;cur_node->next!=NULL;cur_node=cur_node->next)//max尽量向后面位置赋值
    {
        if(_max>=atoi(cur_node->data.date.c_str()))
        {
            p1=cur_node;break;
        }
        else if(_max<atoi(cur_node->data.date.c_str())&&_max>=atoi(cur_node->next->data.date.c_str()))
        {
            p1=cur_node->next;break;
        }
    }
    Node<record> *p2=NULL;
    cur_node=head;
    if(_min<=atoi(cur_node->data.date.c_str()))
    {
            p2=cur_node;
    }
    for(;cur_node->next!=NULL;cur_node=cur_node->next)//min尽量向当前位置赋值
    {
        if(_min>atoi(head->data.date.c_str()))
        {
            break;
        }
        else if(_min<=atoi(cur_node->data.date.c_str())&&_min>atoi(cur_node->next->data.date.c_str()))
        {
            p2=cur_node;break;
        }
    }
    if(atoi(this->GoBottom()->data.date.c_str())>=_min)
    {
        p2=this->GoBottom();
    }
    if(p1==NULL||p2==NULL||p2->n>p1->n)//如果出现都小或都大或者都在中间就不输出
    {
        cout<<"抱歉没有该时间段的记录"<<endl;
    }
    else
    {
        cout<<setfill(' ')<<setw(10)<<"日期"<<setw(10)<<"时间"<<setw(10)<<"消费"<<endl;
        for(cur_node=p1;cur_node->n >= p2->n;)//循环控制输出防止越界
        {
            cout<<setw(10)<<cur_node->data.date<<setw(10)<<cur_node->data.time<<setw(10)<<cur_node->data.expense<<endl;
            if(cur_node->next!=NULL)
            {
                cur_node=cur_node->next;
            }
            else
            {
                break;
            }
        }
    }
}
void LFR::ShowList()const
{
    cout<<"你的余额："<<sum<<endl;
    cout<<"详细消费信息如下："<<endl;
    cout<<setfill(' ')<<setw(10)<<"日期"<<setw(10)<<"时间"<<setw(10)<<"消费"<<endl;
    for(Node<record> *p=head; p!=NULL; p=p->next)
	{
		cout<<setw(10)<<p->data.date<<setw(10)<<p->data.time<<setw(10)<<p->data.expense<<endl;
	}
}

#endif // LFR_H
