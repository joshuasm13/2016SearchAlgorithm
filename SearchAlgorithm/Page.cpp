#include "PageSet.h"
using namespace std;
/*-----------------------------------------------------------------------------
Joshua Moore
jsm4

CPSC 2120 
Prof. Brian Dean

HW 1 | Page Rank | Page.cpp
-----------------------------------------------------------------------------*/

// Return a hash for the string s in the range 0..table_size-1
int hash(string s, int table_size)
{
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}
//-----------------------------------------------------------------------------
// Allocate a table of pointers to Pages, all initialized to NULL 
Page **allocate_table(int size)
{
  Page **table = new Page *[size];
  for (int i=0; i<size; i++)
    table[i] = NULL;
  return table;
}
//-----------------------------------------------------------------------------
Pageset::Pageset()
{
    ifstream in;
    string s;
    size = 0;
    table = NULL;
    num_elems = 0;
    wsize = 0;
    int clockc = 0;

    in.open("webpages.txt");
    while(in>>s){
      if(s == "NEWPAGE")
        size++;
      else if (!(s[4] == ':'))
        wsize++;
      Lclock(clockc++);
    }
    size = size;
    in.close();
 
    table = allocate_table(size);
}
//-----------------------------------------------------------------------------
Pageset::~Pageset()
{
  for (int i=0; i<size; i++) {
    while (table[i] != NULL) {
      Page *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete[] table;
}
//-----------------------------------------------------------------------------
// Inserts a new key.  It is an error if key is already in the set.
int Pageset::insert(string key) {
  int index = 0,C=0, i=0,j,r;
  Page *newpage = NULL;

  index = hash(key,size);
  // if(findp(key,index))
  //   return -1;
  newpage = new Page(key, NULL, 1.0/size, 1.0/size, index);

  newpage->next = table[index];
  table[index]  = newpage;

  return(index);
}
//-----------------------------------------------------------------------------
void Pageset::setword(string set,int i, string key){
  Keyword *Word =  new Keyword(set,NULL,i);
  Word->setHash(size);
  Page *P = table[i];

  while(P!=NULL){
    if(P->KEY == key){
      if (findw(set,i)&&(set[4] == ':')){   
        Word->next = P->Words;
        P->Words = Word;
        P->total++;
      }
    }
    P = P->next;
  }
}
//-----------------------------------------------------------------------------
void Pageset::print(string s){
  int i = hash(s,size);
  Page *P = table[i];

  while(P!=NULL){
    if(P->KEY == s){
      cout<<((int)(P->weight *10000000.0))<<" "<<P->KEY<<endl;
      return;
    }
    P = P->next;
  }  
}
//-----------------------------------------------------------------------------
bool Pageset::findw(string s, int i){
  Page *P = table[i];
  Keyword *K = P->Words;

  if (P==NULL || K == NULL)
    return true;
  
  while(K!=NULL){
    if(K->word == s)
      return false;
    K=K->next;
  }
  return true;
}

bool Pageset::findp(string s, int i){
  Page *P = table[i];

  while(P!=NULL){
    if(P->KEY == s);
      return true;
    P = P->next;
  }
  return false;
}






