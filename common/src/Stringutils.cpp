#include<stringutils>

#include<iostream>
using namespace std;

bool stringutils::equalsIgnoreCase(const char* a,const char* b)
{
 int x=0;
 char A[51],B[51];
 while(a[x]!='\0')
 {
 if(a[x]>=97&&a[x]<=122)
 {
   A[x]=a[x]-32;
 }
 else 
 {
  A[x]=a[x];
 }
  x++;
 }
 A[x]='\0';

 x=0;
 while(b[x]!='\0')
 {
  if(b[x]>=97&&b[x]<=122)
  {
   B[x]=b[x]-32;
  }
  else
  {
   B[x]=b[x];
  }
  x++;
 }
 B[x]='\0'; 
 
 x=0; 
 while(A[x]!='\0'&&B[x]!='\0'&&A[x]==B[x])
 {
  x++;
 }
 if(A[x]=='\0'&&B[x]=='\0')
 {
  return true;
 }
 else
 {
  return false;
 }
}

bool stringutils::compareIgnoreCase(string &a,string &b)
{
 int x=0;
 char A[51],B[51];
 while(a[x]!='\0')
 {
 if(a[x]>=97&&a[x]<=122)
 {
   A[x]=a[x]-32;
 }
 else 
 {
  A[x]=a[x];
 }
  x++;
 }
 A[x]='\0';

 x=0;
 while(b[x]!='\0')
 {
  if(b[x]>=97&&b[x]<=122)
  {
   B[x]=b[x]-32;
  }
  else
  {
   B[x]=b[x];
  }
  x++;
 }
 B[x]='\0'; 
 
 x=0; 
 while(A[x]!='\0'&&B[x]!='\0'&&A[x]==B[x])
 {
  x++;
 }
  return B[x]-A[x];
}
string stringutils::trim(string a)
{
  int e=0,f=a.size()-1;
 while(a[e]==' ')
 e++;
  while(a[f]==' ')
 f--;

 return a.substr(e,f-e+1);
 
}