#include<dl/uomdao>
#include<dl/uom>
#include<dl/iuom>
#include<iostream>
using namespace inventory;
using namespace dataLayer;
using namespace std;
int main(int argn,char **c)
{
 abc::IUnitOfMeasurement *m;

 UnitOfMeasurementDAO mn;

 
 try{
 int x;
 cin>>x;
 cout<<"finding code:"<<argn<<endl;
 m=mn.getByCode(x);
 cout<<"found with title:"<<m->getTitle();

 }catch(DAOException *q)
 {
  cout<<q->what()<<endl;
 }



return 0;
}