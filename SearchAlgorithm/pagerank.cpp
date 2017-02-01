#include "PageSet.h"
using namespace std;
/*-----------------------------------------------------------------------------
Joshua Moore
jsm4

CPSC 2120 
Prof. Brian Dean

HW 1 | Page Rank | pagerank.cpp
-----------------------------------------------------------------------------*/

void Pageset::pageweight(){
  int i,r,j,t,q;
  
  Page *P = NULL;      // Actual Page that weight is being added to
  Page *T = NULL;      // Page that is distributing its weight among its links
  Keyword *L = NULL;   // String that reprents the Page that weight will be 
                       //   added to

  for(r=0;r<50;r++){
    if(table[0]!=NULL)
    Wclock(r);
    for(i=0;i<size;i++){      
      T = table[i];
      while (T!=NULL){
         T->new_weight = 0.1/size;    // Resets new_weight
         T = T->next;
      }  
    } 

    for(i=0;i<size;i++){
      T = table[i]; 
      while(T!= NULL){
        L = T->Words; 
          while(L!=NULL){
            if(L->word[4] == ':'){     
              P = table[L->Hash];                                   
              while(P!=NULL){
                if(P->KEY==L->word){
                  P->new_weight += 0.9 * T->weight/T->total;
                  break;
                }
                P = P->next;
              }     
            }
            L = L->next; 
          }
          T = T->next;
       }
    }
    
    for(i=0;i<size;i++){        
      T = table[i];
      while (T!=NULL){
        T->weight = T->new_weight;   // Updates weight
        T = T->next;
      }  
    }
  }
}
































