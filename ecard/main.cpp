#include <iostream>
#include "eCard.H"
#include "LinkList.h"
#include "LFR.h"
using namespace std;

int main()
{
    record one(200,"20170203","0304");
    record two(130,"21170203","0504");
    record three(230,"20170203","0403");
    record re[3]={one,two,three};
    LFR c("ljx","16122187",re,3);

    LFR b;
    //b=c;
    c.ShowList();

    c.GoTop();
    c.Skip(1);
    cout<<c.isLast();
    //b.ShowList();
    //c.RecountSum();
    //cout<<c.Name()<<c.Id()<<c.NumNodes()<<endl<<c.Sum()<<endl;
    //cout<<b.Name()<<b.Id()<<b.NumNodes()<<endl<<b.Sum()<<endl;
    //c.ShowCurData();
//    record re=c.CurData();



    return 0;
}
