#include<dl/uomdao>
#include<dl/uom>
#include<iostream>
using namespace inventory;
using namespace dataLayer;
int main(int argn,char **c)
{
 UnitOfMeasurement m;
 m.setTitle(c[1]);
 int x;
 cin>>x;
 m.setCode(x);

 UnitOfMeasurementDAO mn;


 try{
 mn.update(&m);
 cout<<"updated with code:"<<m.getCode()<<endl;

 }catch(DAOException *q)
 {
  cout<<q->what()<<endl;
 }



return 0;
}