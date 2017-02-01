#include "PageSet.h"
using namespace std;
/*-----------------------------------------------------------------------------
Joshua Moore
jsm4

CPSC 2120 
Prof. Brian Dean

HW 1 | Page Rank | Words.cpp
-----------------------------------------------------------------------------*/

Word **allocate_Wtable(int size)
{
  Word **table = new Word *[size];
  for (int i=0; i<size; i++)
    table[i] = NULL;
  return table;
}
//-----------------------------------------------------------------------------
Wordset::Wordset()
{
    ifstream in;
    string s;
    size = 4;
    table = allocate_Wtable(size);
    num_elems = 0;
}
Wordset::Wordset(int j)
{
    ifstream in;
    string s;
    size = j;
    table = allocate_Wtable(size);
    num_elems = 0;
}
//-----------------------------------------------------------------------------
Wordset::~Wordset()
{
  for (int i=0; i<size; i++) {
    while (table[i] != NULL) {
      Word *temp = table[i];
      table[i] = table[i]->next;
      delete temp;
    }
  }
  delete[] table;
}
//-----------------------------------------------------------------------------
void Wordset::insert(string key, string link){

    int index = 0,C=0,warmhash, i=0,j;
    Word *newword = NULL;
    index = hash(key, size); 
    Word *T = table[index];
    Word *branch = NULL;
    num_elems++;

    // If index is not empty, if KEY exists set and return
    while (T!=NULL){
      if(T->KEY == key){
          WPage *P = new WPage(link,NULL);
          P->next = T->pages;
          T->pages = P;
      return;
      }
      T=T->next;
    }

    // Allocate structure double the size of table if table is full and 
    //  copy elements
    if (num_elems == size) {
      Word **largetable = NULL;  
      Word *newbranch = NULL;
      largetable = allocate_Wtable(size*2);

      while (C<size){
        branch = table[C];
        while(branch != NULL){
          Word *temp = branch;
          warmhash = hash(branch->KEY,size*2);
          newbranch = new Word(branch->KEY, NULL,branch->pages,warmhash);
          newbranch->ID = warmhash;
          newbranch->next = largetable[warmhash];
          largetable[warmhash] = newbranch;
          branch = branch->next;
          delete temp;
        }
        C++;   
      }
      delete[] table;
      size = size * 2; 
      table = largetable;
    }

    newword = new Word(key,table[index],NULL,index);
    if(table[index] != NULL)
       newword->pages = table[index]->pages;
  
    newword->next = table[index];
    table[index]  = newword;

    WPage *P = new WPage(link,NULL);
    P->next = newword->pages;
    newword->pages = P;
    
}
//-----------------------------------------------------------------------------
void Wordset::PrintSearch(string s,Pageset *Get){
  int i = hash(s,size);
  string o;
  Word *N = table[i];
  string k;
  if(table[i] == NULL){
    cout<<endl<<"No Pages Found. Try another word:" <<endl;
    return;
  }
    
  while(N!=NULL && N->next!=NULL && N->KEY!=s){
    N = N->next;
  }
  
  if(N->KEY==s){
    WPage *W = N->pages;
    while(W!=NULL){
      if (W->link != o){
        Get->print(W->link);
        o = W->link;
      }
      W = W->next;
    }
    cout<<"\n\nSearch results for '"<< s << "' are above.\n\n"<< "---\nEnter a word to search:"<<endl;
  }
  else {
    cout<<endl<<"No Pages Found. Try another word:" <<endl;
  }
}
/*------
bool Wordset::findpage(string link, WPage *word){
  while(word!=NULL){
    if(word->link ==link) return false;
    word = word->next;
  }
  return true;
}
*/










