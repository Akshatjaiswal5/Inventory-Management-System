#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>

using namespace inventory;
using namespace businessLayer;
using namespace std;
int main()
{
 int x;
 cout<<"Enter code:";
 cin>>x;
 
 try{

 UnitOfMeasurementManager manager;
 manager.removeUnitOfMeasurementByCode(x);
 cout<<"removed";
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


}