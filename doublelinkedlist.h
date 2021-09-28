#ifndef __DOUBLE_LINKEDLIST_H__  // # es una DIRECTIVAs al PreCOMPILADOR
#define __DOUBLE_LINKEDLIST_H__ 
#include <cassert>//Leonardo
using namespace std;

template <typename T>
class DoubleLinkedList
{
  class Node
  { private:
      T       m_data;
      Node   *m_pNext, *m_pPrev;
    public:
      // TODO: Completar
      Node(T data, Node *pNext = nullptr, Node *pPrev = nullptr) 
          : m_data(data), m_pNext(pNext), m_pPrev(pPrev) //jose terrones,  Leonardo,Joaquin, Jesus, Carlos Manuel, Christian Rivera, Miguel Ucañay,carlos daniel
      {};
      T         getData()                {   return m_data;    }
      T        &getDataRef()             {   return m_data;    }
      void      setpNext(Node *pNext)    {   m_pNext = pNext;  }
      Node     *getpNext()               {   return m_pNext;   }
      Node    *&getpNextRef()            {   return m_pNext;   }
      void      setpPrev(Node *pPrev)    {   m_pPrev = pPrev;  }
      //jose terrones
      Node     *getpPrev()               {   return m_pPrev;   }//Miguel Ucañay
      Node    *&getpPrevRef()            {   return m_pPrev;   }//Leonardo
      // TODO: Completar
  };
  private:
    Node    *m_pHead = nullptr, 
            *m_pTail = nullptr;
    size_t   m_size  = 0;
    void internal_insert(Node *&rpPrev, T &elem);
  public:
    // DoubleLinkedList() {}
    void    push_front(T elem); // TODO: push_front//changing names Jesus; carlos daniel, Miguel Ucañay; Christian Rivera,joaquin
    void    push_back(T elem); // TODO: push_back//changing names Jesus; carlos daniel, Miguel Ucañay; Christian Rivera,joaquin
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
        // using Node = typename DoubleLinkedList<T>::Node;
        DoubleLinkedList<T> *m_pList;
        DoubleLinkedList<T>::Node *m_pNode;
    public:
        iterator(DoubleLinkedList<T> *pList, DoubleLinkedList<T>::Node *pNode)
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
    class reverse_iterator 
    {private:
        // using Node = typename DoubleLinkedList<T>::Node;
        DoubleLinkedList<T> *m_pList;
        DoubleLinkedList<T>::Node *m_pNode;
    public:
        reverse_iterator(DoubleLinkedList<T> *pList, DoubleLinkedList<T>::Node *pNode)
              : m_pList(pList), m_pNode(pNode) {}
        reverse_iterator(reverse_iterator &other) 
              : m_pList(other.m_pList), m_pNode(other.m_pNode){}
        reverse_iterator(reverse_iterator &&other) // Move constructor
              {   m_pList = move(other.m_pList); // 
                  m_pNode = move(other.m_pNode);
              }
        reverse_iterator operator=(reverse_iterator &iter);
        bool operator==(reverse_iterator iter)   { return m_pNode == iter.m_pNode; }
        bool operator!=(reverse_iterator iter)   { return m_pNode != iter.m_pNode; }
        T &operator*()                   { return m_pNode->getDataRef();   }
        reverse_iterator operator++();
    };
    reverse_iterator rbegin() { reverse_iterator iter(this, m_pTail);
                                return iter;
                              }
    
    reverse_iterator rend()   { reverse_iterator iter(this, nullptr);
                                return iter;
                              }
};

//Leonardo, Ricardo, Miguel Ucañay,Jesus,carlos daniel
template <typename T>
void DoubleLinkedList<T>::push_front(T elem)
{
  Node *pNew = new Node(elem, m_pHead);
  if(m_pHead)
  {
      m_pHead->setpPrev(pNew);
  }
  m_pHead = pNew;
  // Se pone el puntero al anterior
  m_size++;
}

// Leonardo, Ricardo, Miguel Ucañay,Jesus,carlos daniel
template <typename T>
void DoubleLinkedList<T>::push_back(T elem)
{
    Node *pNew = new Node(elem, nullptr, m_pTail);
    if(m_pTail)
    {  m_pTail->setpNext(pNew);
    }
    m_pTail = pNew;
    if(!m_pHead)
    { m_pHead = pNew;   }
    m_size++;
}

// Deprecated
template <typename T>
void DoubleLinkedList<T>::insert_2(T elem)
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

//Leonardo
template <typename T>
void DoubleLinkedList<T>::internal_insert(Node *&rpPrev, T &elem)
{   
  if(!rpPrev || rpPrev->getData() > elem )
  {
    Node *pNew = new Node(elem, rpPrev);
    if(rpPrev){//para verificar que no haya null
      pNew->setpPrev(rpPrev->getpPrev());// 
      rpPrev->setpPrev(pNew);
    }
    rpPrev = pNew;
    m_size++;
  }
  else
    internal_insert(rpPrev->getpNextRef(), elem);
}

//Leonardo
template <typename T>
T DoubleLinkedList<T>::PopHead()
{
    if(m_pHead)
    {
        Node *pNode = m_pHead;
        
        T data = pNode->getData();
        m_pHead = m_pHead->getpNext();
        m_pHead->setpPrev(nullptr);
        delete pNode;
        m_size--;
        return data;
    }
    throw "hola excepcion";
}

template <typename T>
T &DoubleLinkedList<T>::operator[](size_t pos)
{
  assert(pos <= size());
  Node *pTmp = m_pHead;
  for(auto i= 0 ; i < pos ; i++)
    pTmp = pTmp->getpNext();
  return pTmp->getDataRef();
}

template <typename T>
ostream &DoubleLinkedList<T>::print(ostream &os)
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
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::iterator::operator++()
{
    m_pNode = m_pNode->getpNext();
    return *this; 
}

template <typename T>
typename DoubleLinkedList<T>::reverse_iterator DoubleLinkedList<T>::reverse_iterator::operator++()
{
    m_pNode = m_pNode->getpPrev();
    return *this; 
}
#endif