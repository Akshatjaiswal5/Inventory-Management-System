#include<dl/uomdao>
#include<dl/uom>
#include<iostream>
using namespace inventory;
using namespace dataLayer;
int main(int argn,char **c)
{
 UnitOfMeasurement m;
 m.setTitle(string(c[1]));

 UnitOfMeasurementDAO mn;


 try{
 mn.add(&m);
 cout<<"added with code:"<<m.getCode()<<endl;

 }catch(DAOException *q)
 {
  cout<<q->what()<<endl;
 }



return 0;
}