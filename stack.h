#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>
#include "linkedlist.h"

using namespace std;
template <typename T>
class Stack
{
  private:
    LinkedList<T> m_list;
  public:
    Stack() {}
    void push(T n)      {   m_list.insert_at_head(n);   }
    T pop()             {   return m_list.PopHead();    }
};

#endif