#include<dl/uomdao>
#include<dl/uom>
#include<dl/iuom>
#include<iostream>
#include<forward_list>
using namespace inventory;
using namespace dataLayer;
using namespace std;
int main()
{
 abc::IUnitOfMeasurement *m;

 UnitOfMeasurementDAO mn;
 forward_list<abc::IUnitOfMeasurement*> *list;
 try{
 list=mn.getAll();
 int size=mn.getCount();
 cout<<"total:"<<size<<endl;
 for(int i=0;i<size;i++)
 {
  m=list->front();
  list->pop_front();

  cout<<"Title:"<<m->getTitle()<<" code:"<<m->getCode()<<endl;
 }


 }catch(DAOException *q)
 {
  cout<<q->what()<<endl;
 }



return 0;
}