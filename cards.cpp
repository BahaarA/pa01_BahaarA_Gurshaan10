//cards.cpp
//bahaar ahuja & gurshaan sachdeva 
//Implementation of the classes defined in cards.h

#include "cards.h"

#include <iostream>
#include <string>
using namespace std;

//constructor
hand::hand(){root = 0;}

//deconstructor
hand::~hand(){clear(root);}

//deconstructor helper
void hand::clear(card* c){
  if (c) {
    clear(c->l);
    clear(c->r);
    delete c;
  }
}

//converts suit char into an int value
int suitConvertor(const char& suit){
  if(suit == 'c'){
    return 1;
  }else if(suit == 'd'){
    return 2;
  }else if(suit == 's'){
    return 3;
  }else if(suit == 'h'){
    return 4;
  }else{
    return 0;
  }
}

//convers face char into an int value
int faceConvertor(const char& face){
  if(face == 'a'){
    return 1;
  }else if(face == 'j'){
    return 11;
  }else if(face == 'q'){
    return 12;
  }else if(face == 'k'){
    return 13;
  }else if(face == '1' || face == '0'){
    return 10;
  }else{
    return face - '0';
  }
}

//appends cards to tree
void hand::insert(const char suit, const char face){
  if (root == 0){
    root = new card;
    root->suitv = suitConvertor(suit);
    root->facev = faceConvertor(face);
    root->l = 0;
    root->r = 0;
    root->parent = 0;
  }
  else{
    inserth(suit, face, root);
  }
}

//insert helper
void hand::inserth(const char suit, const char face, card* c){
  int fi, si;
  si = suitConvertor(suit);
  fi = faceConvertor(face);
  if(si < c->suitv){
    if(c->l){
      return inserth(suit, face, c->l);
    }
    else{
      c->l = new card;
      c->l->suitv = si;
      c->l->facev = fi;
      c->l->l = 0;
      c->l->r = 0;
      c->l->parent = c;
    }
  }
  else if(si > c->suitv){
    if(c->r){
      return inserth(suit, face, c->r);
    }
    else{
      c->r = new card;
      c->r->suitv = si;
      c->r->facev = fi;
      c->r->l = 0;
      c->r->r = 0;
      c->r->parent = c;
    }
  }
  else{
    if(fi < c->facev){
      if(c->l){
  return inserth(suit, face, c->l);
      }
      else{
  c->l = new card;
  c->l->suitv = si;
  c->l->facev = fi;
  c->l->l = 0;
  c->l->r = 0;
  c->l->parent = c;
      }
    }
    else{
      if(c->r){
  return inserth(suit, face, c->r);
      }
      else{
  c->r = new card;
  c->r->suitv = si;
  c->r->facev = fi;
  c->r->l = 0;
  c->r->r = 0;
  c->r->parent = c;
      }
    }  
  }
}

//print function
void hand::print() const{
  printInOrder(root);
}

//print helper
void hand::printInOrder(card* c) const{
  if(c == NULL){
    return;
  }
  printInOrder(c->l);
  cout << cardToString(c->suitv, c->facev) << endl;
  printInOrder(c->r);
}

//finds card
card* hand::find(card* c){
  return getCardNode(*c, root);
}

//find helper, n is root,
//find helper, n is root,
card* hand::getCardNode(card& c, card* n){
  if(n){
    if(*n == c){
      return n;
    }
    if(c < *n){
      return getCardNode(c, n->l);
    }
    if(c > *n){
      return getCardNode(c, n->r);
    }
  }return NULL;
}

//get successor
card* hand::getSuccessorCard(card* n){
  if(n->r){
    n = n->r;
    while(n->l){
      n = n->l;
    }
    return n;
  }
  else if(n->parent != 0){
    if(n->parent->l == n){
      return n->parent;
    }
    else if(n->parent->r == n){
      n = n->parent;
      while (n->parent){
  if(n->parent->l != n){
    n = n->parent;
  }
  else{
    return n->parent;
  }
      }
    }
  }
  return NULL;
}

//gets predecessor node
card* hand::getPredecessorCard(card* n){
  if(n->l){
    n = n->l;
    while(n->r){
      n = n->r;
    }
    return n;
  }
  else if(n->parent != 0){
    if(n->parent->r == n){
      return n->parent;
    }
    else if(n->parent->l == n){
      n = n->parent;
      while (n->parent){
  if(n->parent->r != n){
    n = n->parent;
  }
  else{
    return n->parent;
  }
      }
    }
  }
  return NULL;
}

//returns max card
card* hand::ismax(card* n){
  card* tmp = n;
  while (tmp->r){
    tmp = tmp->r;
  }
  return tmp;
}

//returns min card
card* hand::ismin(card* n){
  card* tmp = n;
  while(tmp->l){
    tmp = tmp->l;
  }
  return tmp;
}

//removes card n
void hand::removeCard(card* n){
  if(n->l == 0 && n->r == 0){
    if (n == root)
      delete n;
    else if (n == (n->parent->l))
      n->parent->l = 0;
    else
      n->parent->r = 0;
    delete n;
  }
  else if(n->l == 0){
    if (n == root){
      root = n->r;
      root->parent = 0;
      delete n;
    }
    else{
      if (*n->parent < *n){
        n->parent->r = n->r;
  n->r->parent = n->parent;
  delete n;
      }
      else{
        n->parent->l = n->r;
        n->r->parent = n->parent;
  delete n;
      }
    }   
  }
  else if( n->r == 0){
    if (n==root){
      root = n->l;
      n->l->parent = 0;
      delete n;
    }
    else{
      if (*n->parent < *n){
  n->parent->r = n->l;
  n->l->parent = n->parent;
  delete n;
      }
      else{
  n->parent->l = n->l;
  n->l->parent = n->parent;
  delete n;
      }
    }
  }
  else{
    card* sw;
    sw = getPredecessorCard(n);
    //int tmpnums = n->suitv, tmpnumf = n->facev;
    n->suitv = sw->suitv;
    n->facev = sw->facev;
    removeCard(sw);
  }
}

//counts number of cards in hand
int hand::count() const{
  return countHelper(root);
}

//count helper
int hand::countHelper(card* n) const{
  if(n == NULL){
    return 0;
  }
  return 1 + countHelper(n->l) + countHelper(n->r);
}

//convert int value card attributes to string
string cardToString(const int svalue, const int fvalue){
  string s, a, b;
  if(svalue == 1){
    a = "c";
  }else if(svalue == 2){
    a = "d";
  }else if(svalue == 3){
    a = "s";
  }else if(svalue == 4){
    a = "h";
  }

  if(fvalue == 1){
    b = "a";
  }else if(fvalue == 2){
    b = "2";
  }else if(fvalue == 3){
    b = "3";
  }else if(fvalue == 4){
    b = "4";
  }else if(fvalue == 5){
    b = "5";
  }else if(fvalue == 6){
    b = "6";
  }else if(fvalue == 7){
    b = "7";
  }else if(fvalue == 8){
    b = "8";
  }else if(fvalue == 9){
    b = "9";
  }else if(fvalue == 10){
    b = "10";
  }else if(fvalue == 11){
    b = "j";
  }else if(fvalue == 12){
    b = "q";
  }else if(fvalue == 13){
    b = "k";
  }

  s = a + " " + b;
  return s;
}

//overloading == operator
bool operator==(card& c1, card& c2){
  if(c1.suitv == c2.suitv && c1.facev == c2.facev){
    return true;
  }
  else{
    return false;
  }
}

//overloading > operator
bool operator>(card& c1, card& c2){
  if(c1.suitv > c2.suitv){
    return true;
  }
  else if(c1.suitv < c2.suitv){
    return false;
  }
  else{
    if(c1.facev > c2.facev){
      return true;
    }
    else{
      return false;
    }
  }
}

//overloading < operator
bool operator<(card& c1, card& c2){
  if(c1.suitv < c2.suitv){
    return true;
  }
  else if(c1.suitv > c2.suitv){
    return false;
  }
  else{
    if(c1.facev < c2.facev){
      return true;
    }
    else{
      return false;
    }
  }
}

//2nd print card function
void printCards(hand& h1, hand& h2){
  cout << "Alice's cards:" << endl;
  h1.print();
  cout << endl;
  cout << "Bob's cards:" << endl;
  h2.print();
  return;
}

//traverses h1 and deletes matching cards in h1 and h2
void traverseh1(hand& h1, hand& h2, bool& iscomplete){
  card* h1current = h1.ismin(h1.root);
  card* h1max = h1.ismax(h1.root);
  card* fp = h2.find(h1current);
  while(fp == NULL && h1current != h1max && h1.getSuccessorCard(h1current) != NULL){
    h1current = h1.getSuccessorCard(h1current);
    fp = h2.find(h1current);
  }
  if(h1current == h1max && h2.find(h1current)){
    iscomplete = true;
    cout << "Alice picked matching card ";
    cout << cardToString(h1current->suitv, h1current->facev) << endl;
    h1.removeCard(h1current);
    h2.removeCard(fp);
  }
  else if(h1current == h1max){
    iscomplete = true;
  }
  else{
    cout << "Alice picked matching card ";
    cout << cardToString(h1current->suitv, h1current->facev) << endl;
    h1.removeCard(h1current);
    h2.removeCard(fp);
  }
}

//traverses h2 and does the same as h1
void traverseh2(hand& h2, hand& h1, bool& iscomplete){
  card* h2current = h2.ismax(h2.root);
  card* h2min = h2.ismin(h2.root);
  card* fp = h1.find(h2current);
  while(fp == NULL && h2current != h2min && h2.getPredecessorCard(h2current) != NULL){
    h2current = h2.getPredecessorCard(h2current);
    fp = h1.find(h2current);
  }
  if(h2current == h2min){
    iscomplete = true;
  }
  else{
    cout << "Bob picked matching card ";
    cout << cardToString(h2current->suitv, h2current->facev) << endl;
    h2.removeCard(h2current);
    h1.removeCard(fp);
  }
}
