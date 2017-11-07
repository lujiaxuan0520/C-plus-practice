#include <iostream>
#include <string>
#include "eCard.H"
#include "LinkList.h"
#include "LFR.h"
#include <windows.h>
#include <fstream>
#include <vector>
#include <iomanip>
#include <conio.h>

using namespace std;
void init_show()
{
    cout<<setfill('*')<<setw(30)<<'*'<<endl;
    cout<<'*'<<setfill(' ')<<setw(29)<<'*'<<endl;
    cout<<'*'<<setw(29)<<'*'<<endl;
    cout<<'*'<<setw(29)<<'*'<<endl;
    cout<<'*'<<setw(5)<<' '<<"欢迎使用一卡通服务"<<setw(6)<<'*'<<endl;
    cout<<'*'<<setw(29)<<'*'<<endl;
    cout<<'*'<<setw(29)<<'*'<<endl;
    cout<<'*'<<setw(29)<<'*'<<endl;
    cout<<setfill('*')<<setw(30)<<'*'<<endl;
}
void test1(LFR &c)
{
    cout<<"当前账户余额为："<<c.RecountSum()<<endl;
    cout<<"按下任意键以继续";
    getch();
}
void test2(const LFR &c)
{
    c.ShowList();
    cout<<"按下任意键以继续";
    getch();
}
void test3( LFR &c)
{
    string t1,t2;
    cout<<"请输入查询的日期范围：";
    cin>>t1>>t2;
    cout<<"查询结果为："<<endl;
    c.Find(t1,t2);
    cout<<"按下任意键以继续";
    getch();
}

int main()
{
    string student_id,password;
    init_show();
    here:
    cout<<"请输入你的学号：";
    cin>>student_id;                            //手动输入的学号
    string filename=student_id+".txt";          //学生学号对应文件名，如16122198.txt
    //读文件操作
    ifstream istrm(filename);
    if(!istrm)
    {
        fprintf(stderr,"数据库中无该学生！\n",filename.c_str());
        goto here;
    }
    const char* Stu_name=NULL;
    string xname;
    const char* Stu_id=NULL;
    string xid;
    vector<record> vec;                         //临时储存该学生的消费记录
    if(istrm.is_open())
    {
        char buffer[128];
        bool firstline=true;
        while(!istrm.eof())
        {
            istrm.getline(buffer,128);
            if(firstline)
            {
                Stu_name=strtok(buffer," ");
                xname.assign(&Stu_name[0]);
                Stu_id=strtok(NULL," ");
                xid.assign(&Stu_id[0]);
                firstline=false;
            }
            else
            {
                const char* Expense=strtok(buffer," ");
                double expense=atof(Expense);
                const char* date=strtok(NULL," ");
                const char* time=strtok(NULL," ");
                record tmp_record(expense,date,time);
                vec.push_back(tmp_record);
            }
        }
    }
    LFR c(xname,xid,&vec[0],vec.size());      //用从文件中读取到的学生及消费信息构造一个LFR对象
    istrm.close();
    cout<<"请输入你的密码：";
    cin>>password;
    for(int i=1;;i++)
    {
        if(password==student_id)                    //默认密码即为学号
        {
            cout<<"登陆成功！"<<endl;
            cout<<"正在为您跳转，请稍等";
            for(int j=0;j<5;j++)
            {
                Sleep(600);
                cout<<".";
            }
            break;
        }
        else
        {
            if(i==4) exit(-1);
            cout<<"信息有误！请重新输入密码（你还有"<<4-i<<"次机会）：";
            cin>>password;
        }
    }
    system("cls");
    int key;
    while(true)
    {
        system("cls");
        cout<<"当前账户："<<c.Id()<<"  "<<c.Name()<<endl;
        cout<<"请输入您的需求：";
        cout << "\n1--查询账户余额, 2--查看所有消费记录, 3--查找消费记录, 0--退出当前账户: ";
        key = getch() - '0';
        cout << endl;
        if(key==0) break;
        switch(key)
        {
            case 1: test1(c);   break;
            case 2: test2(c);   break;
            case 3: test3(c);   break;
        }
    }
    return 0;
}
