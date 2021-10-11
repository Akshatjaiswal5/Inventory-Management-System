#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<bl/blexception>
#include<stringutils>

#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<dl/daoexception>

#include<map>
#include<forward_list>

using namespace inventory;
using namespace businessLayer;
using namespace stringutils;

#include<iostream>
using namespace std;

bool UnitOfMeasurementTitleComparator::operator()(string *left, string *right)
{
 return *(left)<*(right);
}

UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel;

UnitOfMeasurementManager::DataModel::DataModel()
{
 populateDataStructures();
}
UnitOfMeasurementManager::DataModel::~DataModel()
{}
void UnitOfMeasurementManager::DataModel::populateDataStructures()
{
 forward_list<inventory::dataLayer::abc::IUnitOfMeasurement*> *dlUnitOfMeasurements; 
 inventory::dataLayer::UnitOfMeasurementDAO unitOfMeasurementDAO;
 dlUnitOfMeasurements=unitOfMeasurementDAO.getAll();
  
 inventory::dataLayer::abc::IUnitOfMeasurement* dlUnitOfMeasurement;
 _UnitOfMeasurement* blUnitOfMeasurement;
 forward_list<inventory::dataLayer::abc::IUnitOfMeasurement*>::iterator i;

 int code;
 string *title;

 for(i=dlUnitOfMeasurements->begin();i!=dlUnitOfMeasurements->end();++i)
 {
  dlUnitOfMeasurement=*i;
  code=dlUnitOfMeasurement->getCode();
  title=new string(dlUnitOfMeasurement->getTitle());

  blUnitOfMeasurement= new _UnitOfMeasurement;
  blUnitOfMeasurement->code=code;
  blUnitOfMeasurement->title=title;

  dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement*>(code,blUnitOfMeasurement));
  dataModel.titleWiseMap.insert(pair<string*,_UnitOfMeasurement*>(title,blUnitOfMeasurement));
 
  delete dlUnitOfMeasurement;
 } 

 dlUnitOfMeasurements->clear();
 delete dlUnitOfMeasurements; 
}




UnitOfMeasurementManager::UnitOfMeasurementManager(){}
void UnitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement)
{
 BLException ble;

 if(unitOfMeasurement==NULL)
 {
  ble.setGenericException("Designation required");
  throw ble;
 }

 int code=unitOfMeasurement->getCode();
 string title=unitOfMeasurement->getTitle();


 if(code!=0)
 {
  ble.addPropertyException("code","Code should be zero");
 }

 if(title.length()==0)
 {
  ble.addPropertyException("title","Title required");
 }

 if(title.length()>50)
 {
  ble.addPropertyException("title","Title length must not exceed 50 characters");
 }

 if(ble.hasExceptions())
 throw ble;

 map<string*,_UnitOfMeasurement*>::iterator i=dataModel.titleWiseMap.find(&title);
 if(i!=dataModel.titleWiseMap.end())
 {
  ble.addPropertyException("title","Title already exists with another code");
  throw ble;
 }
 
 try
 {  
  inventory::dataLayer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
  dlUnitOfMeasurement= new inventory::dataLayer::UnitOfMeasurement;

  dlUnitOfMeasurement->setCode(0);
  dlUnitOfMeasurement->setTitle(title); 

  inventory::dataLayer::UnitOfMeasurementDAO unitOfMeasurementDAO;
  unitOfMeasurementDAO.add(dlUnitOfMeasurement);

  code=dlUnitOfMeasurement->getCode();
  delete dlUnitOfMeasurement;
 }
 catch(inventory::dataLayer::DAOException* daoe)
 {
  ble.setGenericException(string(daoe->what()));
  throw ble;
 }

 _UnitOfMeasurement* dsUnitOfMeasurement= new _UnitOfMeasurement;
 
 dsUnitOfMeasurement->code=code;
 string *t=new string(title);
 dsUnitOfMeasurement->title=t;

 dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement*>(code,dsUnitOfMeasurement));
 dataModel.titleWiseMap.insert(pair<string*,_UnitOfMeasurement*>(t,dsUnitOfMeasurement));
 
 unitOfMeasurement->setCode(code);
}

forward_list<abc::IUnitOfMeasurement*>* UnitOfMeasurementManager::getUnitOfMeasurements()
{
 forward_list<abc::IUnitOfMeasurement*>* list= new forward_list<abc::IUnitOfMeasurement*>;
 forward_list<abc::IUnitOfMeasurement*>::iterator listI= list->before_begin();

 map<int,_UnitOfMeasurement*>::iterator i;

 for(i=dataModel.codeWiseMap.begin();i!=dataModel.codeWiseMap.end();i++)
 {
  _UnitOfMeasurement* _unitOfMeasurement;
  _unitOfMeasurement=i->second;

  abc::IUnitOfMeasurement* unitOfMeasurement= new UnitOfMeasurement;
  unitOfMeasurement->setCode(_unitOfMeasurement->code);
  unitOfMeasurement->setTitle(*(_unitOfMeasurement->title));

  listI=list->insert_after(listI,unitOfMeasurement);
 }
 return list;
}

int UnitOfMeasurementManager::getUnitOfMeasurementCount()
{
 return dataModel.codeWiseMap.size();
}

void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement)
{
 BLException ble;

 if(unitOfMeasurement==NULL)
 {
  ble.setGenericException("Designation required");
  throw ble;
 }

 int code=unitOfMeasurement->getCode();
 string title=unitOfMeasurement->getTitle();


 if(code<=0)
 {
  ble.addPropertyException("code","Code should be greater than zero");
 }

 if(title.length()==0)
 {
  ble.addPropertyException("title","Title required");
 }

 if(title.length()>50)
 {
  ble.addPropertyException("title","Title length must not exceed 50 characters");
 }

 if(ble.hasExceptions())
 throw ble;

 map<int,_UnitOfMeasurement*>::iterator i=dataModel.codeWiseMap.find(code);
 if(i==dataModel.codeWiseMap.end())
 {
  ble.addPropertyException("code","Code not found");
  throw ble;
 }

 map<string*,_UnitOfMeasurement*,UnitOfMeasurementTitleComparator>::iterator j=dataModel.titleWiseMap.find(new string(title));
 if(j!=dataModel.titleWiseMap.end()&&j->second->code!=code)
 {
  ble.addPropertyException("title","Title already exists with another code");
  throw ble;
 }

 try
 {
  inventory::dataLayer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
  dlUnitOfMeasurement= new inventory::dataLayer::UnitOfMeasurement;

  dlUnitOfMeasurement->setCode(code);
  dlUnitOfMeasurement->setTitle(title); 

  inventory::dataLayer::UnitOfMeasurementDAO unitOfMeasurementDAO;
  unitOfMeasurementDAO.update(dlUnitOfMeasurement);

  delete dlUnitOfMeasurement;
 }
 catch(inventory::dataLayer::DAOException* daoe)
 {
  ble.setGenericException(string(daoe->what()));
  throw ble;
 }

 _UnitOfMeasurement* oldUnitOfMeasurement= i->second;

 dataModel.codeWiseMap.erase(oldUnitOfMeasurement->code);
 dataModel.titleWiseMap.erase(oldUnitOfMeasurement->title);

 delete oldUnitOfMeasurement->title;
 delete oldUnitOfMeasurement;
 
 _UnitOfMeasurement* newUnitOfMeasurement= new _UnitOfMeasurement;
 
 newUnitOfMeasurement->code=code;
 string *t=new string(title);
 newUnitOfMeasurement->title=t;

 dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement*>(code,newUnitOfMeasurement));
 dataModel.titleWiseMap.insert(pair<string*,_UnitOfMeasurement*>(t,newUnitOfMeasurement));
} 


void UnitOfMeasurementManager::removeUnitOfMeasurementByCode(int code)
{
 BLException ble;

 if(code<=0)
 {
  ble.addPropertyException("code","Code should be greater than zero");
  throw ble;
 }

 map<int,_UnitOfMeasurement*>::iterator i=dataModel.codeWiseMap.find(code);
 if(i==dataModel.codeWiseMap.end())
 {
  ble.addPropertyException("code","Code not found");
  throw ble;
 }

 try
 { 
  inventory::dataLayer::UnitOfMeasurementDAO unitOfMeasurementDAO;
  unitOfMeasurementDAO.remove(i->second->code);
 }
 catch(inventory::dataLayer::DAOException* daoe)
 {
  ble.setGenericException(string(daoe->what()));
  throw ble;
 }

 _UnitOfMeasurement* oldUnitOfMeasurement= i->second;

 dataModel.codeWiseMap.erase(oldUnitOfMeasurement->code);
 dataModel.titleWiseMap.erase(oldUnitOfMeasurement->title);

 delete oldUnitOfMeasurement->title;
 delete oldUnitOfMeasurement; 
}

void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string title)
{
 BLException ble;

 if(title.length()==0)
 {
  ble.addPropertyException("title","Title required");
  throw ble;
 }

 if(title.length()>50)
 {
  ble.addPropertyException("title","Title length must not exceed 50 characters");
  throw ble;
 }

 map<string*,_UnitOfMeasurement*,UnitOfMeasurementTitleComparator>::iterator i=dataModel.titleWiseMap.find(&title);
 if(i==dataModel.titleWiseMap.end())
 {
  ble.addPropertyException("title","Title not found");
  throw ble;
 }

 try
 { 
  inventory::dataLayer::UnitOfMeasurementDAO unitOfMeasurementDAO;
  unitOfMeasurementDAO.remove(i->second->code);
 }
 catch(inventory::dataLayer::DAOException* daoe)
 {
  ble.setGenericException(string(daoe->what()));
  throw ble;
 }

 _UnitOfMeasurement* oldUnitOfMeasurement= i->second;
 dataModel.codeWiseMap.erase(oldUnitOfMeasurement->code);
 dataModel.titleWiseMap.erase(oldUnitOfMeasurement->title);

 delete oldUnitOfMeasurement->title;
 delete oldUnitOfMeasurement; 
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code)
{
 BLException ble;
 if(code<=0)
 {
  ble.addPropertyException("code","Code should be greater than zero");
  throw ble;
 }
 map<int,_UnitOfMeasurement*>::iterator i=dataModel.codeWiseMap.find(code);
 if(i==dataModel.codeWiseMap.end())
 {
  ble.addPropertyException("code","Code not found");
  throw ble;
 }
 _UnitOfMeasurement* _unitOfMeasurement;
 _unitOfMeasurement=i->second;

 abc::IUnitOfMeasurement* unitOfMeasurement= new UnitOfMeasurement;
 unitOfMeasurement->setCode(_unitOfMeasurement->code);
 unitOfMeasurement->setTitle(*(_unitOfMeasurement->title));

 return unitOfMeasurement;
}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string title)
{
 BLException ble;

 if(title.length()==0)
 {
  ble.addPropertyException("title","Title required");
  throw ble;
 }

 if(title.length()>50)
 {
  ble.addPropertyException("title","Title length must not exceed 50 characters");
  throw ble;
 }

 map<string*,_UnitOfMeasurement*,UnitOfMeasurementTitleComparator>::iterator i=dataModel.titleWiseMap.find(&title);
 if(i==dataModel.titleWiseMap.end())
 {
  ble.addPropertyException("title","Title not found");
  throw ble;
 }

 _UnitOfMeasurement* _unitOfMeasurement;
 _unitOfMeasurement=i->second;

 abc::IUnitOfMeasurement* unitOfMeasurement= new UnitOfMeasurement;
 unitOfMeasurement->setCode(_unitOfMeasurement->code);
 unitOfMeasurement->setTitle(*(_unitOfMeasurement->title));

 return unitOfMeasurement;
}
int UnitOfMeasurementManager::codeExists(int code)
{
 if(code<=0)
 return false;

 map<int,_UnitOfMeasurement*>::iterator i=dataModel.codeWiseMap.find(code);
 if(i==dataModel.codeWiseMap.end())
 return false;

 return true;
}
int UnitOfMeasurementManager::titleExists(string title)
{
 if(title.length()==0)
 return false;

 if(title.length()>50)
 return false;

 map<string*,_UnitOfMeasurement*,UnitOfMeasurementTitleComparator>::iterator i=dataModel.titleWiseMap.find(&title);
 if(i==dataModel.titleWiseMap.end())
 return false;

 return true;
}


