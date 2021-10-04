#include <iostream>
#include <vector>
#include "demo.h"

using namespace std;

// Test desde Mac
// g++ -pthread -std=c++17 -o main main.cpp
// COmentario extra de Mac

int main()
{
  //demoQueue();
  //demoSwap();
  vector<TX> v1;
  // demoLinkedList();
  demoLinkedListSorted();
  cout << "Finalizando el programa ..." << endl;
  //demoStack()
}