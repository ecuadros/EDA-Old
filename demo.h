#ifndef __DEMO_H__  
#define __DEMO_H__ 

#include <iostream>
#include <vector>
#include "type.h"
#include "util.h"
#include "stack.h"
#include "queue.h"
#include "doublelinkedlist.h"
#include "operators.h"
#include "operacion.h"
#include "recorrrer.h"

const int nElem = 20;
TX vect[nElem] = {5,30,40, 7,80, 90, 37,25, 54,47, 
                    3, 6, 12, 8, 25, 27, 19, 83, 9, 17};

void demoSwap()
{
  int x = 5, y = 9;
  cout << "x=" << x << ", y=" << y <<endl;
  swap1(x, y);
  cout << "x=" << x << ", y=" << y <<endl;

  double w = 7.3, z = 14.8;
  cout << "w=" << w << ", z=" << z <<endl;
  swap1(w, z);
  cout << "w=" << w << ", z=" << z <<endl;
}

void demoStack()
{
  Stack<T1> stack;
  Stack<T1> *pStack = new Stack<T1>;

  auto w = "hola";
  auto x = 0; 
  for( x = 0 ; x < nElem ; x++ )
     stack.push(x+x);
  
  for( x = 0 ; x < nElem ; x++ )
  {
    auto y = stack.pop();
    cout << y << endl;
  }
}

void demoLinkedList()
{
  vect[10] = 53;
  int z = 5;
  DoubleLinkedList<TX> mylist;
  for(auto x=0; x<10; x++)
  {   mylist.push_back(vect[x]);
      cout << mylist << " ." <<endl;
  }
  cout << endl;

  for(auto x=10; x< nElem; x++)
  {   mylist.push_front(vect[x]);
      cout << mylist << endl;
  }
  
  auto x1 = mylist[7];
  mylist[5] = 14;

  cout << endl;
  
  recorrer(mylist);
  mylist.insert_2(170);
  recorrer(mylist, fx);  cout << endl;
  

  try
  {
      auto dato = mylist.PopHead();
      cout << "abc" << endl;
  }
  catch(int n) 
  {
    cout << "Excepcion atrapada ... puedes continuar !!!" <<endl;
  }
  catch(double n) 
  {
    cout << "Excepcion de doubles atrapada ... puedes continuar !!!" <<endl;
  } 
  catch(exception n) 
  {
    cout << "Excepcion generica atrapada ... puedes continuar !!!" <<endl;
  }  
  catch( ... )
  {
      cout << "todo lo demas atrapada ... puedes continuar !!!" <<endl;
  }
}

void demoLinkedListSorted2()
{
  DoubleLinkedList<TX> mylist;
  for(auto x=0; x<nElem; x++)
  {   cout << "> " << vect[x] << endl; 
      mylist.insert_2(vect[x]);
      recorrer(mylist, fx);  cout << endl;
  }
  cout << endl;
}

void demoLinkedListSorted()
{
  DoubleLinkedList<TX> mylist;
  // LinkedList<string> myliststring;
  
  for(auto x=0; x<nElem; x++)
  {   cout << "> " << vect[x] << endl; 
      mylist.insert(vect[x]);
  }
  cout << "Lista en orden: ";
  recorrer(mylist, fx);  cout << endl;
  cout << "Lista invertida: ";
  recorrer_inverso(mylist, fx);  cout << endl;
}

#endif
