#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<iomanip>
using namespace std;
struct login
{
    char name[100];
    char password[100];
};
struct node
{
    char name[100];
    char type[10];
    char sub_type[10];
    int call;
    int use;
    int no_use;
    char reuse[10];
};
void enter();
void del();
void display();
void display1();
void query();
void user_list();
void del_user();
void modify();
int main()
{
    int admin=0;
    char a;
    cout<<"\n New User(Y/N) : ";
    cin>>a;
    system("cls");
    if(a=='N' || a=='n')
    {
     int b=3;
     char temp[100];
     char temp1[100];
     ifstream f1;
     f1.open("login.txt",ios::binary);
     while(b--)
     {
        getchar();
        cout<<"\nEnter login credentials :- ";
        cout<<"\nUsername : ";
        gets(temp);
        cout<<"\nPassword : ";
        gets(temp1);
        login l1;
        f1.read((char*)&l1,sizeof(l1));
        int i=0;
        while(f1!=NULL)
        {

            if(strcmp(temp,"admin")==0 && strcmp(temp1,"admin")==0)
            {
                admin=1;
                break;
            }
            if(strcmp(temp,l1.name)==0 && strcmp(temp1,l1.password)==0)
            {
                i=1;
                break;
            }
            f1.read((char*)&l1,sizeof(l1));
        }
        if(admin==1)
        {
            break;
        }
        if(i==1)
        {
            break;
        }
        else
        {
            cout<<"\nIncorrect Username/Password";
        }
    }
    f1.close();
    if(b!=-1)
    {
        if(admin==1)
        {
            int choice=1;
            system("cls");
            cout<<"\n                                      Welcome Admin.!";
            while(choice!=9)
            {
             cout<<"\nEnter your choice : ";
             cout<<"\n1.Enter new component";
             cout<<"\n2.Delete Component";
             cout<<"\n3.Modify Component";
             cout<<"\n4.Delete User";
             cout<<"\n5.Display List";
             cout<<"\n6.Display List(type)";
             cout<<"\n7.Query Component";
             cout<<"\n8.User list";
             cout<<"\n9.EXIT";
             cin>>choice;
             system("cls");
             switch(choice)
             {
                 case 1: enter();
                         break;
                 case 2: del();
                         break;
                 case 3: modify();
                         break;
                 case 4: del_user();
                         getchar();
                         break;
                 case 5: display();
                         break;
                 case 6: display1();
                         getchar();
                         break;
                 case 7: query();
                         getchar();
                         break;
                 case 8: user_list();
                         getchar();
                         getchar();
                         break;
                 case 9: cout<<"ADMIN LOGGING-OFF";
                         return(0);

             }
             system("cls");
            }
        }
        else
        {
         int choice=1;
         cout<<"\nUSER sucessfully Logged in";
         while(choice)
         {
             cout<<"\nEnter your choice : ";
             cout<<"\n1.Query component";
             cout<<"\n0.EXIT";
             cin>>choice;
             if(choice==1)
              query();

         }

        }
    }
    else
    {
        cout<<"\nYour 3 Attempts are over";
        exit(0);
    }
   }
   else
   {
       login l1;
       getchar();
     l:cout<<"\nWelcome new user.!";
       cout<<"\nCreate your Profile : ";
       cout<<"\nLogin ID : ";
       gets(l1.name);
       cout<<"\nPassword : ";
       gets(l1.password);
       if(strcmp(l1.name,"admin")==0)
       {
           cout<<"Username NOT allowed.!";
           cout<<"Enter again";
           goto l;
       }
       ofstream f1;
       f1.open("login.txt",ios::binary | ios::app);
       f1.write((char*)&l1,sizeof(l1));
       cout<<"\nNew user sucessfully added.!";
       f1.close();
    }
   }
   void enter()
{
    getchar();
    node temp;
    cout<<"\nEnter Name                 : ";
    gets(temp.name);
    cout<<"\nEnter Type                 : ";
    gets(temp.type);
    cout<<"\nEnter Sub-type             : ";
    gets(temp.sub_type);
    cout<<"\nReUsable/Non-ReUsable(Y/N) : ";
    gets(temp.reuse);
    temp.no_use=0;
    temp.call=0;
    temp.use=0;
    ofstream f1;
    f1.open("component.txt",ios::binary | ios::app);
    f1.write((char*)&temp,sizeof(temp));
    f1.close();
    cout<<"\nComponent Added to file sucessfully..!";
    getchar();
}
void del()
{
    getchar();
    char name[100];
    cout<<"\nEnter name : ";
    gets(name);
    int b=0;
    node temp;
    ifstream f1;
    f1.open("component.txt",ios::binary);
    f1.read((char*)&temp,sizeof(node));
    ofstream f2;
    f2.open("c.txt",ios::binary | ios::trunc);
    while(f1!=NULL)
    {
        if(strcmp(temp.name,name)!=0)
           {
               f2.write((char*)&temp,sizeof(temp));
           }
        f1.read((char*)&temp,sizeof(node));
    }
    f1.close();
    f2.close();
    remove("component.txt");
    rename("c.txt","component.txt");
    cout<<"\nDeletion Process completed.!";
    getchar();
}
void display()
{
    node temp;
    ifstream f1;
    f1.open("component.txt",ios::binary);
    f1.read((char*)&temp,sizeof(node));
    cout<<"\n";
    cout<<left<<setw(15)<<"NAME"<<setw(15)<<"TYPE"<<setw(15)<<"REUSE"<<setw(15)<<"CALLS"<<setw(10)<<"USE"<<setw(15)<<"NOT-USED";
    while(f1!=NULL)
    {
        cout<<"\n"<<setw(15)<<temp.name<<setw(15)<<temp.type<<setw(15)<<temp.reuse<<setw(15)<<temp.call<<setw(15)<<temp.use<<setw(15)<<temp.no_use;
        f1.read((char*)&temp,sizeof(node));
    }
    f1.close();
    getchar();
    getchar();
}
void display1()
{
    int a;
    cout<<"\nEnter your choice :-\n1.Design\n2.Code\n3.Other";
    cin>>a;
    char name[100];
    if(a==1) strcpy(name,"design");
    else if(a==2) strcpy(name,"code");

    node temp;
    ifstream f1;
    f1.open("component.txt",ios::binary);
    f1.read((char*)&temp,sizeof(node));
    cout<<"\n";
    cout<<left<<setw(15)<<"NAME"<<setw(15)<<"TYPE"<<setw(15)<<"REUSE"<<setw(15)<<"CALLS"<<setw(10)<<"USE"<<setw(15)<<"NOT-USED";
    while(f1!=NULL)
    {
        if(a==3)
        {
         if((strcmp(temp.type,"design")!=0) && (strcmp(temp.type,"code")!=0))
             cout<<"\n"<<setw(15)<<temp.name<<setw(15)<<temp.type<<setw(15)<<temp.reuse<<setw(15)<<temp.call<<setw(15)<<temp.use<<setw(15)<<temp.no_use;
         f1.read((char*)&temp,sizeof(node));
        }
        else
        {
            if(strcmp(temp.type,name)==0)
             cout<<"\n"<<setw(15)<<temp.name<<setw(15)<<temp.type<<setw(15)<<temp.reuse<<setw(15)<<temp.call<<setw(15)<<temp.use<<setw(15)<<temp.no_use;
         f1.read((char*)&temp,sizeof(node));
        }
    }
    f1.close();
    getchar();
}
void query()
{
    getchar();
    cout<<"\nEnter component name : ";
    char temp[100];
    gets(temp);
    ifstream f1;
    ofstream f2;
    node n1;
    f1.open("component.txt",ios::binary);
    f1.read((char*)&n1,sizeof(n1));
    f2.open("temp.txt",ios::binary);
    int i=0;
    while(f1!=NULL)
    {
        if(strcmp(n1.name,temp)==0)
        {
            cout<<left<<setw(15)<<"NAME"<<setw(15)<<"TYPE"<<setw(15)<<"REUSE"<<setw(15)<<"CALLS"<<setw(10)<<"USE"<<setw(15)<<"NOT-USED";
            cout<<"\n"<<setw(15)<<n1.name<<setw(15)<<n1.type<<setw(15)<<n1.reuse<<setw(15)<<n1.call<<setw(15)<<n1.use<<setw(15)<<n1.no_use;
            i=1;
            int p;
            cout<<"\nWant to use? (0/1)";
            cin>>p;
            if(p)
            {
              n1.call=n1.call+1;
              n1.use=n1.use+1;

            }
            else
            {
                n1.call=n1.call+1;
                n1.no_use=n1.no_use+1;

            }
        }
        f2.write((char*)&n1,sizeof(n1));
        f1.read((char*)&n1,sizeof(n1));
    }
    if(i==0)
    {
        cout<<"\nComponent not found.!";
    }
    f1.close();
    f2.close();
    remove("component.txt");
    rename("temp.txt","component.txt");
}
void user_list()
{
    ifstream f1;
    login l1;
    f1.open("login.txt",ios::binary);
    f1.read((char*)&l1,sizeof(l1));
    cout<<"\n"<<left<<setw(15)<<"USERNAME"<<setw(15)<<"PASSWORD";
    while(f1!=NULL)
    {
        cout<<"\n"<<left<<setw(15)<<l1.name<<setw(15)<<l1.password;
        f1.read((char*)&l1,sizeof(l1));
    }
    f1.close();
    cout<<"\n";
}
void del_user()
{
    user_list();
    cout<<"\n";
    login l1;
    ifstream f1;
    ofstream f2;
    f1.open("login.txt",ios::binary);
    f2.open("temp.txt",ios::binary);
    char temp[100];
    getchar();
    cout<<"\nEnter user-name";
    gets(temp);
    f1.read((char*)&l1,sizeof(l1));
    int i=0;
    while(f1!=NULL)
    {
        if(strcmp(l1.name,temp)!=0)
        {
            f2.write((char*)&l1,sizeof(l1));
        }
        else
        {
            i=1;
        }
        f1.read((char*)&l1,sizeof(l1));
    }
    if(i)
    {
        cout<<"\nDeletion Sucessfull.!";
    }
    else
    cout<<"\nUser Not found";

    f1.close();
    f2.close();
    remove("login.txt");
    rename("temp.txt","login.txt");
    user_list();
}
void modify()
{
    ifstream f1;
    ofstream f2;
    char temp[100];
    getchar();
    cout<<"\nEnter the component name to be modified : ";
    gets(temp);
    f1.open("component.txt",ios::binary);
    f2.open("temp.txt",ios::binary);
    node n1;
    f1.read((char*)&n1,sizeof(n1));
    int i=0;
    while(f1!=NULL)
    {
        if(strcmp(temp,n1.name)==0)
        {
            i=1;
            cout<<"\nComponent found.!";
            int choice;
            cout<<"\nEdit type(1/0)";
            cin>>choice;
            getchar();
            if(choice)
            {
                gets(n1.type);
            }
            cout<<"\nEdit sub-type(1/0)";
            cin>>choice;
            getchar();
            if(choice)
            {
                gets(n1.sub_type);
            }
            cout<<"\nEdit Re-use field(1/0)";
            cin>>choice;
            getchar();
            if(choice)
            {
                gets(n1.reuse);
            }
        }
        f2.write((char*)&n1,sizeof(n1));
        f1.read((char*)&n1,sizeof(n1));
    }
    if(i)
    {
        cout<<"\nSucessful update";
        getchar();
    }
    else
    cout<<"\nComponent not found";

    f1.close();
    f2.close();
    remove("component.txt");
    rename("temp.txt","component.txt");
    getchar();
}
