#ifndef LFR_H
#define LFR_H
#include "eCard.h"
#include "LinkList.h"
#include <string>
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
    LFR & operator=(const LFR &list)
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
    double Sum()
    {
        return sum;
    }
    double CurNodeExpense()
    {
        return cur_node->data.expense;
    }
    string Name()
    {
        return name;
    }
    string Id()
    {
        return ID;
    }
    double RecountSum()
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

private:
    double sum;//余额
    string name;//对象姓名
    string ID;//对象学号
};
#endif // LFR_H
