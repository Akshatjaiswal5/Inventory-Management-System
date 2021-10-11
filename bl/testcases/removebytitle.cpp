#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>

using namespace inventory;
using namespace businessLayer;
using namespace std;
int main()
{
 string x;
 cout<<"Enter title:";
 cin>>x;
 
 try{

 UnitOfMeasurementManager manager;
 manager.removeUnitOfMeasurementByTitle(x);
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