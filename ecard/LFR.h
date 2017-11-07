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
    LFR(string Name="",string id="",const record *t=NULL,int n=0):LinkList(t,n),name(Name),ID(id) //构造函数
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
    void InsBeforeHeadNode(const record &t);//重载插入头节点
    void DeleteCurNode();                   //重载删除当前结点
    void FreeList();                        //重载释放链表
    void ShowList()const;                   //输出链表
    void Find(const string &a,const string &b);//寻找到时间范围为a~b的消费记录并输出
    double RecountSum();                    //重新根据结点数据计算余额

private:
    double sum;//余额
    string name;//对象姓名
    string ID;//对象学号
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
    //捕获当前结点的前一个结点
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
    cout<<setfill(' ')<<setw(10)<<"日期"<<setw(10)<<"时间"<<setw(10)<<"消费"<<endl;
    bool isFind=false;
    for(cur_node=head;cur_node!=NULL;cur_node=cur_node->next)
    {
        if(_min<=atoi(cur_node->data.date.c_str())&&_max>=atoi(cur_node->data.date.c_str()))
        {
            isFind=true;
            cout<<setw(10)<<cur_node->data.date<<setw(10)<<cur_node->data.time<<setw(10)<<cur_node->data.expense<<endl;
        }
    }
    if(!isFind) cout<<"未查询到相关记录！"<<endl;
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
