#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>

using namespace inventory;
using namespace businessLayer;
using namespace std;
int main()
{
 UnitOfMeasurement uom;
 uom.setCode(0);
 string title;
 cout<<"Enter title:";
 cin>>title;
 uom.setTitle(title);
 
 try{

 UnitOfMeasurementManager manager;
 manager.addUnitOfMeasurement(&uom);
 cout<<"added";
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