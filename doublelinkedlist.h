#ifndef __DOUBLE_LINKEDLIST_H__  
#define __DOUBLE_LINKEDLIST_H__ 
#include <cassert>//Leonardo
#include "linkedlist.h"

using namespace std;

// Falta Traits
template <typename T>
class DoubleLinkedList : public LinkedList<T>
{
  class NodeDLL : public NodeLE
  { private:
      NodeDLL   *m_pPrev;
    public:
      // TODO: Completar
      NodeDLL(T data, NodeDLL *pNext = nullptr, NodeDLL *pPrev = nullptr) 
          : NodeLE(data, pNext), m_pPrev(pPrev)
      {};
      void      setpPrev(NodeDLL *pPrev)    {   m_pPrev = pPrev;  }
      //jose terrones
      NodeDLL     *getpPrev()               {   return m_pPrev;   }//Miguel Ucañay
      NodeDLL    *&getpPrevRef()            {   return m_pPrev;   }//Leonardo
  };
  public:
    // DoubleLinkedList() {}
    void    push_front(T elem); // TODO: push_front//changing names Jesus; carlos daniel, Miguel Ucañay; Christian Rivera,joaquin
    void    push_back(T elem); // TODO: push_back//changing names Jesus; carlos daniel,

    void insert(T elem);
    NodeLE *internal_insert(NodeLE *&rpPrev, T &elem);
    // Aqui
    T       PopHead();
    virtual NodeLE *CreateNode(T &data, NodeLE *pNext){ return new NodeDLL(data, pNext); }

    template <typename C>
    class general_iterator
    {
      protected:
        // using NodeDLL = typename DoubleLinkedList<T>::NodeDLL;
        DoubleLinkedList<T> *m_pList;
        DoubleLinkedList<T>::NodeDLL *m_pNodeDLL;
      public:
        general_iterator(DoubleLinkedList<T> *pList, DoubleLinkedList<T>::NodeDLL *pNodeDLL)
                        : m_pList(pList), m_pNodeDLL(pNodeDLL) {}
        general_iterator(general_iterator &other) 
              : m_pList(other.m_pList), m_pNodeDLL(other.m_pNodeDLL){}
        general_iterator(general_iterator &&other) // Move constructor
              {   m_pList = move(other.m_pList);
                  m_pNodeDLL = move(other.m_pNodeDLL);
              }
        C operator=(C &iter);
        bool operator==(C iter)   { return m_pNodeDLL == iter.m_pNodeDLL; }
        bool operator!=(C iter)   { return m_pNodeDLL != iter.m_pNodeDLL; }
        T &operator*()            { return m_pNodeDLL->getDataRef();   }
        DoubleLinkedList<T>::NodeDLL *&  getNodeDLLPtrRef() { return m_pNodeDLL;   }
    };
    
    //agregar class iterator dentro de linkedlist by jose terrones
    class iterator : public general_iterator<iterator>
    {
    public:
        iterator(DoubleLinkedList<T> *pList, DoubleLinkedList<T>::NodeDLL *pNodeDLL)
              :  general_iterator<iterator>(pList, pNodeDLL) {}
        iterator operator++() { general_iterator<iterator>::m_pNodeDLL = general_iterator<iterator>::m_pNodeDLL->getpNext();  
                                return *this;
                              }
    };
    iterator begin() { iterator iter(this, m_pHead);    return iter;    }
    iterator end()   { iterator iter(this, nullptr);    return iter;    }

    class reverse_iterator : public general_iterator<reverse_iterator>
    {
    public:
        reverse_iterator(DoubleLinkedList<T> *pList, DoubleLinkedList<T>::NodeDLL *pNodeDLL)
              :  general_iterator<reverse_iterator>(pList, pNodeDLL) {}
        reverse_iterator operator++(){  general_iterator<reverse_iterator>::m_pNodeDLL = general_iterator<reverse_iterator>::m_pNodeDLL->getpPrev();
                                        return *this;
                                     }
    };
    reverse_iterator rbegin() { reverse_iterator iter(this, m_pTail); return iter; }
    reverse_iterator rend()   { reverse_iterator iter(this, nullptr); return iter; }
};

//Leonardo, Ricardo, Miguel Ucañay,Jesus,carlos daniel
template <typename T>
void DoubleLinkedList<T>::push_front(T elem)
{
  LinkedList<T>::push_front(elem);
  if(m_pHead->getpNext())
      m_pHead->getpNext()->setpPrev(m_pHead);
}

// Leonardo, Ricardo, Miguel Ucañay,Jesus,carlos daniel
template <typename T>
void DoubleLinkedList<T>::push_back(T elem)
{
    Node *pTail = m_pTail;
    LinkedList<T>::push_back(elem);
    m_pTail->setpPrev(pTail);
}
 
template <typename T>
void LinkedList<T>::insert(T elem)
{   
    NodeLE *&pParent = findPrev(m_pHead, elem);
    NodeLE *pNew = CreateNode(elem);
    CreateBridge(pParent, pNew, pNew->getpNextRef());
    CreateBridge(       , pNew, pNew->getpPrevRef());
}

//Leonardo
template <typename T>
NodeLE *DoubleLinkedList<T>::internal_insert(NodeDLL *&rpPrev, T &elem)
{  
   NodeDLL *pNew = LinkedList<T>::internal_insert(rpPrev);
  if(!rpPrev || rpPrev->getData() > elem )
  {
    NodeDLL *pNew = CreateNode(elem, rpPrev);
    if(rpPrev)  //para verificar que no haya null
    {
      pNew->setpPrev(rpPrev->getpPrev());// 
      rpPrev->setpPrev(pNew);
    }
    else
      pNew->setpPrev(m_pTail);
    rpPrev = pNew;
    if( !pNew->getpNext() ) // Es el ultimo
      m_pTail = pNew;
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
        NodeDLL *pNodeDLL = m_pHead;
        
        T data = pNodeDLL->getData();
        m_pHead = m_pHead->getpNext();
        m_pHead->setpPrev(nullptr);//TODO: -- REVISAR---
        delete pNodeDLL;
        m_size--;
        return data;
    }
    throw "hola excepcion"; // Create custom exception pending
}

#endif