#include<dl/uomdao>
#include<dl/uom>
#include<dl/iuom>
#include<iostream>
using namespace inventory;
using namespace dataLayer;
using namespace std;
int main(int argn,char **c)
{

 UnitOfMeasurementDAO mn;

 
 try{
 int x;
 cin>>x;
 cout<<"deleting code:"<<x<<endl;
 mn.remove(x);
 cout<<"removed";

 }catch(DAOException *q)
 {
  cout<<q->what()<<endl;
 }



return 0;
}