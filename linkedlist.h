#ifndef __LINKEDLIST_H__  // # es una DIRECTIVAs al PreCOMPILADOR
#define __LINKEDLIST_H__ 
#include <cassert>//Leonardo
using namespace std;

template <typename T>
class LinkedList
{
  class Node
  { private:
      T       m_data;
      Node   *m_pNext;
    public:
      Node(T data, Node *pNext = nullptr) : m_data(data), m_pNext(pNext)
      {};
      T         getData()                {   return m_data;    }
      T        &getDataRef()             {   return m_data;    }
      void      setpNext(Node *pNext)    {   m_pNext = pNext;  }
      Node     *getpNext()               {   return m_pNext;   }
      Node    *&getpNextRef()            {   return m_pNext;   }
  };
  private:
    Node    *m_pHead = nullptr, 
            *m_pTail = nullptr;
    size_t   m_size  = 0;
    void internal_insert(Node *&rpPrev, T &elem);
  public:
    // LinkedList() {}
    void    insert_at_head(T elem);
    void    insert_at_tail(T elem);
    void    insert_2(T elem);

    void insert(T elem)
    {   internal_insert(m_pHead, elem);   }
    T       PopHead();
    size_t  size()  const       { return m_size;       }
    bool    empty() const       { return size() == 0;  }

    ostream & print(ostream &os);
    T &operator[](size_t pos); 
    
    //agregar class iterator dentro de linkedlist by jose terrones
    class iterator 
    {private:
        // using Node = typename LinkedList<T>::Node;
        LinkedList<T> *m_pList;
        LinkedList<T>::Node *m_pNode;
    public:
        iterator(LinkedList<T> *pList, LinkedList<T>::Node *pNode)
              : m_pList(pList), m_pNode(pNode) {}
        iterator(iterator &other) 
              : m_pList(other.m_pList), m_pNode(other.m_pNode){}
        iterator(iterator &&other) // Move constructor
              { // m_pList = other.m_pList;  other.m_pList = nullptr;
                m_pList = move(other.m_pList); // 
                // m_pNode = other.m_pNode;  other.m_pNode = nullptr;
                m_pNode = move(other.m_pNode);
              }
        iterator operator=(iterator &iter);
        bool operator==(iterator iter)   { return m_pNode == iter.m_pNode; }
        bool operator!=(iterator iter)   { return m_pNode != iter.m_pNode; }
        T &operator*()                   { return m_pNode->getDataRef();   }
        iterator operator++();
        iterator operator++(int );
    };
    iterator begin() { iterator iter(this, m_pHead);
                      return iter;
                     }
    iterator end()   { iterator iter(this, nullptr);
                        return iter;
                      }
};

template <typename T>
void LinkedList<T>::insert_at_head(T elem)
{
  Node *pNew = new Node(elem, m_pHead);
  m_pHead = pNew;
  m_size++;
}

template <typename T>
void LinkedList<T>::insert_at_tail(T elem)
{
    Node *pNew = new Node(elem);
    if(m_pTail)
    {  m_pTail->setpNext(pNew);
    }
    m_pTail = pNew;
    if(!m_pHead)
    { m_pHead = pNew;   }
    m_size++;
}

template <typename T>
void LinkedList<T>::insert_2(T elem)
{
    // Insercion en la cabeza
    if(!m_pHead || m_pHead->getData() > elem )
    {
      Node *pNew = new Node(elem, m_pHead);
      m_pHead = pNew;
    }
    else // Aqui hay que buscar su posicion e insertarlo
    {
      Node **pTmp = &m_pHead;
      while(*pTmp && elem > (*pTmp)->getData())
      {
        pTmp = &(*pTmp)->getpNextRef();
      }
      Node *pNew = new Node(elem, *pTmp);
      *pTmp = pNew; // Error !!! se esta modificandop el pTmp y 
                   // no el puntero del nodo anterior
    }
}
// internal_insert(m_pHead, elem);
template <typename T>
void LinkedList<T>::internal_insert(Node *&rpPrev, T &elem)
{   
  if(!rpPrev || rpPrev->getData() > elem )
  {
    Node *pNew = new Node(elem, rpPrev);
    rpPrev = pNew;
  }
  else
    internal_insert(rpPrev->getpNextRef(), elem);
}

template <typename T>
T LinkedList<T>::PopHead()
{
    if(m_pHead)
    {
        Node *pNode = m_pHead;
        T data = pNode->getData();
        m_pHead = m_pHead->getpNext();
        delete pNode;
        m_size--;
        return data;
    }
    throw "hola excepcion";
}

template <typename T>
T &LinkedList<T>::operator[](size_t pos)
{
  assert(pos <= size());
  Node *pTmp = m_pHead;
  for(auto i= 0 ; i < pos ; i++)
    pTmp = pTmp->getpNext();
  return pTmp->getDataRef();
}

template <typename T>
ostream &LinkedList<T>::print(ostream &os)
{
  Node *pNode = m_pHead;
  while(pNode)
  {
    os << pNode->getData() << ", ";
    pNode = pNode->getpNext();
  }
  return os;
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++()
{
    m_pNode = m_pNode->getpNext();
    return *this; 
}

#endif