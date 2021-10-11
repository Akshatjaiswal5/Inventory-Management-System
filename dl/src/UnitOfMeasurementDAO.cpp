#include<dl/iuom>
#include<dl/uom>
#include<dl/daoexception>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<fstream>
#include<stringutils>
#include<string.h>
#include<dl/IUnitOfMeasurementDAO>
using namespace inventory;
using namespace dataLayer;
using namespace stringutils;


void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement* i) 
{
 const string vtitle=i->getTitle();
 string title=string(trim(vtitle));

 if(title.length()==0)
 throw new DAOException("Title required, length is 0");

 if(title.length()>50)
 throw new DAOException("Title length cannot exceed 50 characters");

 Header header;
 _UnitOfMeasurement _unitOfMeasurement;

 fstream dfile(DATA_FILE,ios::in|ios::out|ios::binary);
 
 if(dfile.fail())
 {
  fstream datafile(DATA_FILE,ios::app|ios::binary);
  header.lastCode=1;
  header.recordCount=1;
  datafile.write((char *)&header,sizeof(Header));
  _unitOfMeasurement.code=1;
  strcpy(_unitOfMeasurement.title,title.c_str());
  datafile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
  datafile.close();
  i->setCode(1);
  return; 
 }

 dfile.read((char *)&header,sizeof(Header));
 if(dfile.fail())
 {
  dfile.clear();
  dfile.seekg(0);dfile.seekp(0);
  header.lastCode=1;
  header.recordCount=1;
  dfile.write((char *)&header,sizeof(Header));
  _unitOfMeasurement.code=1;
  strcpy(_unitOfMeasurement.title,title.c_str());
  dfile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
  dfile.close();
  i->setCode(1);
  return; 
 }


 while(1)
 {
  dfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(dfile.fail())
  break;

  if(equalsIgnoreCase(_unitOfMeasurement.title,title.c_str()))
  {
   dfile.close();
   throw new DAOException(title+string(" exists."));
  }
 
 }
  dfile.clear();
  header.lastCode++;
  header.recordCount++;

  _unitOfMeasurement.code=header.lastCode;
  strcpy(_unitOfMeasurement.title,title.c_str());
 
  dfile.seekp(0,ios::end);
  dfile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  dfile.seekp(0,ios::beg);
  dfile.write((char *)&header,sizeof(Header));
  dfile.close();

  i->setCode(_unitOfMeasurement.code);

}

void UnitOfMeasurementDAO::update(abc::IUnitOfMeasurement* i) 
{
 const string vtitle= i->getTitle();
 int code=i->getCode();

 if(code<0)
 throw new DAOException("Code Invalid");

 string title=trim(vtitle);
 if(title.length()==0)
 throw new DAOException("Title required, length is 0");

 if(title.length()>50)
 throw new DAOException("Title length cannot exceed 50 characters");

 Header header;
 _UnitOfMeasurement _unitOfMeasurement;

 fstream dfile(DATA_FILE,ios::in|ios::out|ios::binary);
 if(dfile.fail())
 throw new DAOException("Not Found");

 dfile.read((char *)&header,sizeof(Header));
 if(dfile.fail())
 throw new DAOException("Not Found");
 long pos;
 bool found=false;
 while(1)
 {
  dfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(dfile.fail())
  break;

  if(equalsIgnoreCase(_unitOfMeasurement.title,title.c_str()))
  throw new DAOException("Title already exists "); 

  if(_unitOfMeasurement.code==code)
  { 
    found=true;
    pos=dfile.tellp();
    pos-=sizeof(_unitOfMeasurement);
  }
 }

 if(!found)
 throw new DAOException("Not Found");

 dfile.clear();
 dfile.seekg(pos,ios::beg);
 dfile.seekp(pos,ios::beg);

 _unitOfMeasurement.code=code;
 strcpy(_unitOfMeasurement.title,title.c_str());
 dfile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

 dfile.close();
}
void UnitOfMeasurementDAO::remove(int code)
{
 if(code<0)
 throw new DAOException("Invalid code");

 Header header;
 _UnitOfMeasurement _unitOfMeasurement;
 fstream dfile(DATA_FILE,ios::in|ios::out|ios::binary);

 if(dfile.fail())
 throw new DAOException("Invalid code");


 dfile.read((char *)&header,sizeof(Header));
 if(dfile.fail())
 {
  dfile.close();
  throw new DAOException("Invalid code");
 }

 bool found=false;
 while(1)
 {
  dfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(dfile.fail())
  break;

  if(_unitOfMeasurement.code==code)
  {
   found=true;
   break;
  } 
 }

 if(!found)
 throw new DAOException("Invalid code");

 dfile.clear();
 dfile.seekg(0,ios::beg);
 dfile.seekp(0,ios::beg);

 
 
 fstream tmpfile("tmp.tmp",ios::in|ios::out|ios::trunc|ios::binary);

 dfile.read((char *)&header,sizeof(Header));
 header.recordCount--;
 tmpfile.write((char *)&header,sizeof(Header));

 while(1)
 {
  dfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(dfile.fail())
  break;

  if(_unitOfMeasurement.code==code)
  continue; 

  tmpfile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
 
 }

 tmpfile.clear();
 tmpfile.seekg(0,ios::beg);
 tmpfile.seekp(0,ios::beg);

 dfile.close();
 
 fstream newfile(DATA_FILE,ios::in|ios::out|ios::trunc|ios::binary);
 
 tmpfile.read((char *)&header,sizeof(Header));
 newfile.write((char *)&header,sizeof(Header));

 while(1)
 {
  tmpfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(tmpfile.fail())
  break;

  newfile.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
 }

 tmpfile.close();
 newfile.close();
}
abc::IUnitOfMeasurement* UnitOfMeasurementDAO::getByCode(int code)
{ 
 Header header;
 _UnitOfMeasurement _unitOfMeasurement;
 fstream dfile(DATA_FILE,ios::in|ios::out|ios::binary);
 if(dfile.fail())
 {
  dfile.close();
  throw new DAOException("Not Found");
 }

 dfile.read((char *)&header,sizeof(Header));
 if(dfile.fail())
 {
  dfile.close();
  throw new DAOException("Not Found");
 }

 bool found=false;
 while(1)
 {
  dfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(dfile.fail())
  break;

  if(_unitOfMeasurement.code==code)
  {
   found=true;
   break;
  } 
 }
 
 if(!found)
 {
  dfile.close();
  throw new DAOException("Not Found");
 }


 dfile.close();
 abc::IUnitOfMeasurement *u=new UnitOfMeasurement;
 u->setCode(_unitOfMeasurement.code);
 u->setTitle(string(_unitOfMeasurement.title));
 return u;
}
abc::IUnitOfMeasurement* UnitOfMeasurementDAO::getByTitle(string title)
{ 
 title=trim(title);
 if(title.length()==0)
 throw new DAOException("Title required, length is 0");

 if(title.length()>50)
 throw new DAOException("Title length cannot exceed 50 characters");

 Header header;
 _UnitOfMeasurement _unitOfMeasurement;
 fstream dfile(DATA_FILE,ios::in|ios::out|ios::binary);
 if(dfile.fail())
 {
  dfile.close();
  throw new DAOException("Not Found");
 }

 dfile.read((char *)&header,sizeof(Header));
 if(dfile.fail())
 {
  dfile.close();
  throw new DAOException("Not Found");
 }

 bool found=false;
 while(1)
 {
  dfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(dfile.fail())
  break;


  if(equalsIgnoreCase(_unitOfMeasurement.title,title.c_str()))
  {
   found=true;
   break;
  } 
 }
 
 if(!found)
 {
  dfile.close();
  throw new DAOException("Not Found");
 }

 dfile.close();
 abc::IUnitOfMeasurement *u=new UnitOfMeasurement;
 u->setCode(_unitOfMeasurement.code);
 string s(_unitOfMeasurement.title);
 u->setTitle(s);
 return u;
}
forward_list<abc::IUnitOfMeasurement*>* UnitOfMeasurementDAO::getAll() 
{
 Header header;
 _UnitOfMeasurement _unitOfMeasurement; 

 forward_list<abc::IUnitOfMeasurement*> *list= new forward_list<abc::IUnitOfMeasurement*>;

 fstream dfile(DATA_FILE,ios::in|ios::out|ios::binary);
 if(dfile.fail())
 {
  dfile.close();
  return list;
 }

 dfile.read((char *)&header,sizeof(Header));
 if(dfile.fail())
 {
  dfile.close();
  return list;
 }

 
 forward_list<abc::IUnitOfMeasurement*>::iterator i=list->before_begin();
 while(1)
 {
  dfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(dfile.fail())
  break;
  
  abc::IUnitOfMeasurement *u=new UnitOfMeasurement;
  u->setCode(_unitOfMeasurement.code);
  string s(_unitOfMeasurement.title);
  u->setTitle(s); 
  i=list->insert_after(i,u);
 }
 
 dfile.close();
 return list; 
}
int UnitOfMeasurementDAO::getCount() 
{
 Header header;
 fstream dfile(DATA_FILE,ios::in|ios::out|ios::binary);
 if(dfile.fail())
 {
  dfile.close();
  return 0;
 }

 dfile.read((char *)&header,sizeof(Header));
 if(dfile.fail())
 {
  dfile.close();
  return 0;
 }

 dfile.close();
 return header.recordCount;
}
int UnitOfMeasurementDAO::codeExists(int code)
{ 
 if(code<0)
 return false;

 Header header;
 _UnitOfMeasurement _unitOfMeasurement;
 fstream dfile(DATA_FILE,ios::in|ios::out|ios::binary);
 if(dfile.fail())
 {
  dfile.close();
  return false;
 }

 dfile.read((char *)&header,sizeof(Header));
 if(dfile.fail())
 {
  dfile.close();
  return false;
 }

 bool found=false;
 while(1)
 {
  dfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(dfile.fail())
  break;

  if(_unitOfMeasurement.code==code)
  {
   found=true;
   break;
  } 
 }

 dfile.close();
 return found;
}
int UnitOfMeasurementDAO::titleExists(string title)
{ 
 title=trim(title);
 if(title.length()==0)
 return false;

 if(title.length()>50)
 return false;

 Header header;
 _UnitOfMeasurement _unitOfMeasurement;
 fstream dfile(DATA_FILE,ios::in|ios::out|ios::binary);
 if(dfile.fail())
 {
  dfile.close();
  return false;
 }

 dfile.read((char *)&header,sizeof(Header));
 if(dfile.fail())
 {
  dfile.close();
  return false;
 }

 bool found=false;
 while(1)
 {
  dfile.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));

  if(dfile.fail())
  break;


  if(equalsIgnoreCase(_unitOfMeasurement.title,title.c_str()))
  {
   found=true;
   break;
  } 
 }
 
 dfile.close();
 return found;
}

                                                         