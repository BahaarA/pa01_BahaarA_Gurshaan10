//test.cpp
#include "cards.h"

#include <iostream>
#include <string>
using namespace std;

//appends cards to hand in that order
void testappend(){
  cout << "Appending h 9, c k, s 3, c a, h j, d 3 to hand" <<endl;

void successor(){
  //checks for successor
}


int main(){
  hand h1, h2;
  h1.insert('d', '9');
  h1.insert('s', '1'); //10
  h1.insert('h', 'j');

  bool all = true;
  int testnum = getTest();
  if (testnum){
    all = false;
  }
  
  return 0;
}
