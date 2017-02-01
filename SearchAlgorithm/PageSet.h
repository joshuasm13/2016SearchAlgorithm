#ifndef Pageset_H  
#define Pageset_H
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <assert.h>
#include <time.h>
/*-----------------------------------------------------------------------------
Joshua Moore
jsm4

CPSC 2120 
Prof. Brian Dean

HW 1 | Page Rank | PageSet.h
-----------------------------------------------------------------------------*/

using namespace std;

int hash(string s, int table_size);
void Lclock(int clock);
void Wclock(int clock);

// Links (Structure 1) | Used in Page Rank algorithm
struct Keyword {
  string word;
  int Hash;
  Keyword *next = NULL;
  int ID;
  Keyword(string w, Keyword *k, int i){word = w; next = k, ID = i;}
  Keyword(){word = ""; next = NULL;};
  void setHash(int s) {Hash = hash(word,s);}
};

// Pages (Structure 1) | Used in Page Rank algorithm
struct Page {
  double weight;
  double new_weight;
  int total;
  string KEY;
  int ID;
  Keyword *Words = NULL;
  Page *next = NULL;
  Page(string k, Page *n, double w, double o,int i) {KEY = k; next = n; new_weight = w; weight = o; ID = i;total =0;}
  Page() { KEY = ""; next = NULL; total = 0; weight = 0, new_weight = 0;}
  
};

// Pages pointing to its links (Structure 1) | Used in Page Rank algorithm
class Pageset {

 private: 
  Page **table = NULL;  // array of pointers to linked lists
  int num_elems;
  int size;      // size of table, as currently allocated
  int wsize;
 public:
  Pageset();
  ~Pageset();

  int  insert(string key);
  void print(string s);
  void setword(string K, int i, string key);
  bool findw(string s, int i);
  bool findp(string s, int i);
  void pageweight();
  int getwsize(){return wsize;}
  int getsize(){return size;}
  int gete(){return num_elems;}
};

//----------------------------------------------------------------------------------
// Links (Structure 2)
struct WPage{
  string link;
  WPage *next = NULL;
  WPage(string l, WPage *n){link=l; next=n;}
};
// Words (Structure 2)
struct Word {
  string KEY;
  int ID;
  Word *next = NULL;
  WPage *pages = NULL;
  Word(string k, Word *w, WPage *n, int i) {KEY = k; next = w; pages = n; ID = i;}
  Word() { KEY = ""; next = NULL; }
  
};
// Words pointing to corresponding URLs (Structure 2)
class Wordset {

 private: 
  Word **table = NULL;  // array of pointers to linked lists
  int size;      // size of table, as currently allocated
  int num_elems;
 public:
  Wordset(int j);
  Wordset();
  ~Wordset();
  void PrintSearch(string s, Pageset *Get);
  void insert(string key,string link);
  bool findpage(string link, WPage *word);
  int getsize(){return size;}
  int gete(){return num_elems;}
};



























#endif
