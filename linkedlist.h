#ifndef __LINKEDLIST_H__  
#define __LINKEDLIST_H__ 
#include <cassert>
using namespace std;


template <typename T>
class LinkedList
{protected:
  class NodeLE
  { protected:
      T       m_data;
      NodeLE   *m_pNext;
    public:
      // TODO: Completar
      NodeLE(T data, NodeLE *pNext = nullptr) 
          : m_data(data), m_pNext(pNext)
      {};
      T         getData()                {   return m_data;    }
      T        &getDataRef()             {   return m_data;    }
      void      setpNext(NodeLE *pNext)    {   m_pNext = pNext;  }
      NodeLE     *getpNext()               {   return m_pNext;   }
      NodeLE    *&getpNextRef()            {   return m_pNext;   }
  };
  private:
    NodeLE    *m_pHead = nullptr, 
              *m_pTail = nullptr;
    size_t   m_size  = 0;
    NodeLE *&internal_insert(NodeLE *&rpPrev, T &elem);
  public:
    
    void    push_front(T elem); 
    void    push_back(T elem); 
    void    insert_2(T elem);

    void insert(T elem);
    T       PopHead();
    size_t  size()  const       { return m_size;       }
    bool    empty() const       { return size() == 0;  }

    ostream & print(ostream &os);
    T &operator[](size_t pos); 
    
    virtual NodeLE *CreateNode(T &data, NodeLE *pNext){ return new NodeLE(data, pNext); }

    template <typename C>
    class general_iterator
    {
      protected:
        LinkedList<T> *m_pList;
        LinkedList<T>::NodeLE *m_pNode;
      public:
        general_iterator(LinkedList<T> *pList, LinkedList<T>::NodeLE *pNode)
                        : m_pList(pList), m_pNode(pNode) {}
        general_iterator(general_iterator &other) 
              : m_pList(other.m_pList), m_pNode(other.m_pNode){}
        general_iterator(general_iterator &&other) // Move constructor
              {   m_pList = move(other.m_pList);
                  m_pNode = move(other.m_pNode);
              }
        C operator=(C &iter);
        bool operator==(C iter)   { return m_pNode == iter.m_pNode; }
        bool operator!=(C iter)   { return m_pNode != iter.m_pNode; }
        T &operator*()            { return m_pNode->getDataRef();   }
        LinkedList<T>::NodeLE *&  getNodePtrRef() { return m_pNode;   }
    };
    
    class iterator : public general_iterator<iterator>
    {
    public:
        iterator(LinkedList<T> *pList, LinkedList<T>::NodeLE *pNode)
              :  general_iterator<iterator>(pList, pNode) {}
        iterator operator++() { general_iterator<iterator>::m_pNode = general_iterator<iterator>::m_pNode->getpNext();  
                                return *this;
                              }
    };
    iterator begin() { iterator iter(this, m_pHead);    return iter;    }
    iterator end()   { iterator iter(this, nullptr);    return iter;    }
};


template <typename T>
void LinkedList<T>::push_front(T elem)
{
  NodeLE *pNew = CreateNode(elem);
  pNew->setpNext(m_pHead);
  m_pHead = pNew;
  m_size++;
}


template <typename T>
void LinkedList<T>::push_back(T elem)
{
    NodeLE *pNew = new NodeLE(elem, nullptr, m_pTail); // TODO
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
    
    if(!m_pHead || m_pHead->getData() > elem )
    {
      NodeLE *pNew = new NodeLE(elem, m_pHead);
      m_pHead = pNew;
    }
    else 
    {
      NodeLE **pTmp = &m_pHead;
      while(*pTmp && elem > (*pTmp)->getData())
      {
        pTmp = &(*pTmp)->getpNextRef();
      }
      NodeLE *pNew = new NodeLE(elem, *pTmp);
      *pTmp = pNew; 
                   
    }
}

template <typename T>
void LinkedList<T>::insert(T elem)
{   
    NodeLE *&pParent = findPrev(m_pHead, elem);
    NodeLE *pNew = CreateNode(elem);
    CreateBridge(pParent, pNew, pNew->getpNextRef());
}

template <typename T>
typename LinkedList <T>
NodeLE *&LinkedList<T>::findPrev(NodeLE *&rpPrev, T &elem)
{   
  if(!rpPrev || rpPrev->getData() > elem )
     return findPrev(pParent->getpNextRef(), elem);
  return rpPrev;
}

template <typename T>
NodeLE *&LinkedList<T>::internal_insert(NodeLE *&rpPrev, T &elem)
{   
  if(!rpPrev || rpPrev->getData() > elem )
  {
    NodeLE *pNew = CreateNode(elem, rpPrev);
    rpPrev = pNew;
    if( !pNew->getpNext() ) 
      m_pTail = pNew;
    m_size++;
    return rpPrev;
  }
  else
    return internal_insert(rpPrev->getpNextRef(), elem);
}


template <typename T>
T LinkedList<T>::PopHead()
{
    if(m_pHead)
    {
        NodeLE *pNode = m_pHead;
        
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
  NodeLE *pTmp = m_pHead;
  for(auto i= 0 ; i < pos ; i++)
    pTmp = pTmp->getpNext();
  return pTmp->getDataRef();
}

template <typename T>
ostream &LinkedList<T>::print(ostream &os)
{
  NodeLE *pNode = m_pHead;
  while(pNode)
  {
    os << pNode->getData() << ", ";
    pNode = pNode->getpNext();
  }
  return os;
}

#endif