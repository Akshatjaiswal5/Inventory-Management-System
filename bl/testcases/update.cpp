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
 int x;
 cout<<"Enter code:";
 cin>>x;
 uom.setCode(x);
 string title;
 cout<<"Enter title:";
 cin>>title;
 uom.setTitle(title);
 
 try{

 UnitOfMeasurementManager manager;
 manager.updateUnitOfMeasurement(&uom);
 cout<<"updated";
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