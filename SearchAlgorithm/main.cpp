#include "PageSet.h"
using namespace std;
/*-----------------------------------------------------------------------------
Joshua Moore
jsm4

CPSC 2120 
Prof. Brian Dean

HW 1 | Page Rank | main.cpp
-----------------------------------------------------------------------------*/

int main(){
  cout<<"\n---\nLoading. Please Wait"<<flush;

  ifstream in;
  string s;
  string k;
  Pageset NP;
  Page *P = NULL;
  int i,z, clockc = 0;
  clock_t begin, end;

  in.open("webpages.txt");

  begin = clock();
  
 // Pages URLs pointing to its links
  while(in>>s){
    if(s == "NEWPAGE"){
      in>>s;
      k = s;
      i = NP.insert(s);
    }
    else if (s[4] == ':'){
      NP.setword(s, i, k);
    }
    Lclock(clockc++);
  }

  in.close();
  in.open("webpages.txt");

 // Create Structure 2 (Inverted Index)
  Wordset NW= Wordset(NP.getwsize());

  while(in>>s){
    if(s == "NEWPAGE"){
      in>>s;
      k = s;
    }
    else if(s[4] == ':'){

    }
    else {
      NW.insert(s,k);
    }
    Lclock(clockc++);
  }
  in.close();

  end = clock();
  cout<<endl<<"Structures loaded in: "<<(end-begin)*.000001<<" seconds."<<endl;
  cout<<"\nComputing Page Rank"<<flush;
  begin = clock();

 // Page Rank
  NP.pageweight();

  end = clock();
  cout<<endl<<"Page Rank in: "<<(end-begin)*.000001<<" seconds. (50 iterations)"<<endl;
  cout<<"\nDone. Enter a word to search: \n";

  while(cin>>s){
    NW.PrintSearch(s,&NP);
  }

  return(0);
}
void Lclock(int clock){
  if(clock%1300000==0)
    cout<<"."<<flush;
}
void Wclock(int clock){
  if(clock%1==0)
    cout<<"."<<flush;
}




