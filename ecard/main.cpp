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
    cout<<'*'<<setw(5)<<' '<<"��ӭʹ��һ��ͨ����"<<setw(6)<<'*'<<endl;
    cout<<'*'<<setw(29)<<'*'<<endl;
    cout<<'*'<<setw(29)<<'*'<<endl;
    cout<<'*'<<setw(29)<<'*'<<endl;
    cout<<setfill('*')<<setw(30)<<'*'<<endl;
}
void test1(LFR &c)
{
    cout<<"��ǰ�˻����Ϊ��"<<c.RecountSum()<<endl;
    cout<<"����������Լ���";
    getch();
}
void test2(const LFR &c)
{
    c.ShowList();
    cout<<"����������Լ���";
    getch();
}
void test3( LFR &c)
{
    string t1,t2;
    cout<<"�������ѯ�����ڷ�Χ��";
    cin>>t1>>t2;
    cout<<"��ѯ���Ϊ��"<<endl;
    c.Find(t1,t2);
    cout<<"����������Լ���";
    getch();
}

int main()
{
    string student_id,password;
    init_show();
    here:
    cout<<"���������ѧ�ţ�";
    cin>>student_id;                            //�ֶ������ѧ��
    string filename=student_id+".txt";          //ѧ��ѧ�Ŷ�Ӧ�ļ�������16122198.txt
    //���ļ�����
    ifstream istrm(filename);
    if(!istrm)
    {
        fprintf(stderr,"���ݿ����޸�ѧ����\n",filename.c_str());
        goto here;
    }
    const char* Stu_name=NULL;
    string xname;
    const char* Stu_id=NULL;
    string xid;
    vector<record> vec;                         //��ʱ�����ѧ�������Ѽ�¼
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
    LFR c(xname,xid,&vec[0],vec.size());      //�ô��ļ��ж�ȡ����ѧ����������Ϣ����һ��LFR����
    istrm.close();
    cout<<"������������룺";
    cin>>password;
    for(int i=1;;i++)
    {
        if(password==student_id)                    //Ĭ�����뼴Ϊѧ��
        {
            cout<<"��½�ɹ���"<<endl;
            cout<<"����Ϊ����ת�����Ե�";
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
            cout<<"��Ϣ�����������������루�㻹��"<<4-i<<"�λ��ᣩ��";
            cin>>password;
        }
    }
    system("cls");
    int key;
    while(true)
    {
        system("cls");
        cout<<"��ǰ�˻���"<<c.Id()<<"  "<<c.Name()<<endl;
        cout<<"��������������";
        cout << "\n1--��ѯ�˻����, 2--�鿴�������Ѽ�¼, 3--�������Ѽ�¼, 0--�˳���ǰ�˻�: ";
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
