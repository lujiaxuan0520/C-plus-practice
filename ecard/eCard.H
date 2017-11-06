#ifndef eCard_H
#define eCard_H
#include <string>
#include <iostream>
#include<cstdlib>
//#include "LFR.h"
using namespace std;
class record
{
public:
    record(double e=0,string d="",string t=""):expense(e),date(d),time(t)
    {
    }
    friend ostream& operator<<(ostream& out,record &r)
    {
        cout<<r.expense<<"\t"<<r.date<<"\t"<<r.time;
        return out;
    }
    friend class LFR;
private:
    double expense;
    string date;
    string time;
};

#endif // eCard_H
