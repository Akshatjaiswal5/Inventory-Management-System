#include<stdlib.h>
#include<iostream>
using namespace std;
int main()
{
 int x,y=1;
 while(y)
 {
  fflush(stdin);
  getchar();
  system("cls");
  cout<<"Select an option:"<<endl;
  cout<<"1.add"<<endl;
  cout<<"2.update"<<endl;
  cout<<"3.get by code"<<endl;
  cout<<"4.get by title"<<endl;  
  cout<<"5.remove by code"<<endl;
  cout<<"6.remove by title"<<endl;
  cout<<"7.get all"<<endl;
  cout<<"8.exit"<<endl;

  cin>>x;

  switch(x)
  {
   case 1: system("add"); continue;
   case 2: system("update"); continue;
   case 3: system("get"); continue;
   case 4: system("getbytitle"); continue;
   case 5: system("remove"); continue;
   case 6: system("removebytitle"); continue;
   case 7: system("getall");continue;
   case 8: y=0;continue;
   default:cout<<"Enter a valid response"<<endl; continue;
  }
 }
 return 0;
}