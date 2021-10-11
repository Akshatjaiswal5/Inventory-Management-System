#include<iostream>
#include<bl/uom>
#include<bl/iuom>
#include<bl/uommanager>
#include<bl/blexception>
#include<forward_list>
using namespace inventory;
using namespace businessLayer;
using namespace std;

int main()
{
 abc::IUnitOfMeasurement *m;

 UnitOfMeasurementManager mn;

 
 try{
 int x;
 cout<<"Enter code: ";
 cin>>x;
 cout<<"finding code:"<<x<<endl;
 
 if(mn.codeExists(x))
 cout<<"found"<<endl;

 m=mn.getUnitOfMeasurementByCode(x);
 cout<<"found with title:"<<m->getTitle();

 }
 catch(BLException ble)
 {
  if(ble.hasGenericException())
  cout<<ble.getGenericException()<<endl;

  if(ble.hasPropertyException("code"))
  cout<<"code problem: "<<ble.getPropertyException("code")<<endl;

  if(ble.hasPropertyException("title"))
  cout<<"title problem: "<<ble.getPropertyException("title")<<endl;
 }


return 0;
}