#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>
#include "doublelinkedlist.h"//Joaquin Farfan // Christian Rivera

using namespace std;
template <typename T>
class Stack
{
  private:
    DoubleLinkedList<T> m_list; //jose terrones
  public:
    Stack() {}
    void push(T n)      {   m_list.push_front(n);   }
    T pop()             {   return m_list.PopHead();    }
};

#endif