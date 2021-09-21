#include <iostream>
#include <vector>

#include "type.h"
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"
#include "operators.h"
#include "operacion.h"

using namespace std;

const int nElem = 20;
TX vect[nElem] = {5,30,40, 7,80, 90, 3,25, 54,47, 
                    3, 6, 12, 8, 25, 27, 19, 83, 9, 17};

// Test desde Mac
// g++ -pthread -std=c++17 -o main main.cpp
// COmentario extra de Mac

template <typename T>
void swap1(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

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

void fx(TX &x)
{  cout << x << "  "; }

void inc(TX &x)
{  ++x; }

template <typename Container, typename F>
void recorrer(Container &container, F fobj)
{
  typename Container::iterator iter = container.begin();
  for(; iter != container.end() ; ++iter)
      fobj(*iter);
}

template <typename Container>
void recorrer(Container &container)
{
    recorrer(container, fx);  cout << endl; // recorre imprimiendo
    recorrer(container, inc);  // recorre incrementando
    recorrer(container, fx);  cout << endl; // recorre imprimiendo

    // funciones lambda
    recorrer(container, [](TX &n){ n-= 5;}); cout << endl; // -5 a todos
    recorrer(container, fx);  cout << endl; // recorre imprimiendo
    
    OperacionEspecial<TX> ope;
    recorrer(container, ope);  
    recorrer(container, fx);  cout << endl;
}

void demoLinkedList()
{
  vect[10] = 53;
  int z = 5;
  LinkedList<TX> mylist;
  // LinkedList<string> myliststring;
  for(auto x=0; x<10; x++)
  {   mylist.insert_at_tail(vect[x]);
      cout << mylist << " ." <<endl;
  }
  cout << endl;

  for(auto x=10; x< nElem; x++)
  {   mylist.insert_at_head(vect[x]);
      cout << mylist << endl;
  }
  
  auto x1 = mylist[7];
  mylist[5] = 14;

  cout << endl;
  
  recorrer(mylist);
  mylist.insert_2(170);
  recorrer(mylist, fx);  cout << endl;
  /*while( !mylist.empty() )
  {   
      auto dato = mylist.PopHead();
      cout << "dato removido: " << dato << endl;
      cout << mylist <<endl;
  }*/

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

void demoQueue()
{
  /*Queue<TX> queue;
  for(auto x=0; x<10; x++)
  {
    queue.insert(vect[x]);
    cout << queue << endl;
  }
  cout << endl;

  for(auto x=0; x<10; x++)
  {
      auto dato = queue.pop();
      cout << "dato removido: " << dato << endl;
      cout << queue <<endl;
  }*/
}

void demoLinkedListSorted2()
{
  LinkedList<TX> mylist;
  // LinkedList<string> myliststring;
  for(auto x=0; x<nElem; x++)
  {   cout << "> " << vect[x] << endl; 
      mylist.insert_2(vect[x]);
      recorrer(mylist, fx);  cout << endl;
  }
  cout << endl;
}

void demoLinkedListSorted()
{
  LinkedList<TX> mylist;
  // LinkedList<string> myliststring;
  for(auto x=0; x<nElem; x++)
  {   cout << "> " << vect[x] << endl; 
      mylist.insert(vect[x]);
      recorrer(mylist, fx);  cout << endl;
  }
  cout << endl;
}

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