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
 
 cout<<"finding title:"<<c[1]<<endl;
 m=mn.getByTitle(c[1]);
 cout<<"found with code:"<<m->getTitle()<<" "<<m->getCode();

 }catch(DAOException *q)
 {
  cout<<q->what()<<endl;
 }



return 0;
}