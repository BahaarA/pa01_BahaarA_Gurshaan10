#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

bool iscomplete = false;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //hand *h1 = new hand, *h2 = new hand;
  hand h1, h2;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    h1.insert(line[0], line[2]);
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    h2.insert(line[0], line[2]);
  }
  cardFile2.close();

  int count = 0;
  while(!iscomplete){
    if(count % 2 == 0){
      traverseh1(h1, h2, iscomplete);
    }
    else{
      traverseh2(h2, h1, iscomplete);
    }
    count++;
  }

  cout << endl;

  printCards(h1, h2);

  //delete h1;
  //delete h2;

  return 0;
}