#include<iostream>
#include<bl/uom>
#include<bl/iuom>
#include<bl/uommanager>
#include<forward_list>
using namespace inventory;
using namespace businessLayer;

int main()
{
abc::IUnitOfMeasurement *uom;
UnitOfMeasurementManager manager;
forward_list<abc::IUnitOfMeasurement*>* unitOfMeasurements= manager.getUnitOfMeasurements();
forward_list<abc::IUnitOfMeasurement*>::iterator i;

cout<<"total: "<<manager.getUnitOfMeasurementCount()<<endl;
for(i=unitOfMeasurements->begin();i!=unitOfMeasurements->end();i++)
{
uom=*i;
cout<<uom->getCode()<<","<<uom->getTitle()<<endl;
}
return 0;
}
