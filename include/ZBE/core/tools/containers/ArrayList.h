/**
 * Copyright 2011 Batis Degryll Ludo
 * @file arrayList.h
 * @since 2015/02/08
 * @date 2015/04/03
 * @author Degryll
 * @brief A list in an static array.
 */

#ifndef CORE_TOOLS_CONTAINERS_ARRAYLIST_H_
#define CORE_TOOLS_CONTAINERS_ARRAYLIST_H_

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/containers/Ticket.h"
#include "ZBE/core/tools/containers/ArrayListIterator.h"

namespace zbe {

template <class Value>
class ArrayListIter;

/** \brief A node for ArrayList
 *
 *  Composed of a value and the index of the next node.
 */
template <class Value>
struct ArrayListNode {
  Value value;
  unsigned next;
};

/** \brief A node for ArrayList
 *
 *  Composed of a value and the index of the next node.
 */
template <class Value>
class ArrayList {
  public:
    ArrayList(unsigned capacity);
    ArrayList(const ArrayList<Value>& arraylist);

    virtual ~ArrayList();

    unsigned insert(Value value);
    //void erase(unsigned index);  // cant be erased directly, the iterator will erase it

    unsigned getCapacity() {return (c);}
    unsigned getSize() {return (s);}
    unsigned getIndex() {return (i);}

    bool isEmpty() {return (s==0);}

    ArrayListIter<Value> begin() {return (ArrayListIter<Value>(this));}
    ArrayListIter<Value> end() {return (ArrayListIter<Value>(this,-1));}

    ArrayListNode<Value>& operator[](unsigned idx);
    const ArrayListNode<Value>& operator[](unsigned idx) const;

  private:
    ArrayListNode<Value> *values;
    unsigned i;
    unsigned f;
    unsigned c;
    unsigned s;
};

template <class Value>
ArrayList<Value>::ArrayList(unsigned capacity) : i(-1), f(0), c(capacity), s(0) {
  values = new ArrayListNode<Value>[capacity];
  for(unsigned i = 0; i < c; i++) {
     values[i].next = i+1;
  }
  values[c-1].next = -1;
}

template <class Value>
ArrayList<Value>::ArrayList(const ArrayList<Value>& arraylist) : i(arraylist.i), f(arraylist.f), c(arraylist.c), s(arraylist.s) {
  values = new ArrayListNode<Value>[c];
  for(unsigned i = 0; i < c; i++) {
     values[i].next = i+1;
  }
  values[c-1].next = -1;
  ArrayListIter<Value> it = arraylist.begin();
  for(;it != arraylist.end(); ++it) {
    this->insert(*it);
  }
}

template <class Value>
ArrayList<Value>::~ArrayList() {
  delete[] values;
}

template <class Value>
unsigned ArrayList<Value>::insert(Value value) {
  if(s < c) {
    values[f].value = value;
    unsigned aux = values[f].next;
    values[f].next = i;
    i = f;
    f = aux;
    s++;
  } else {
    SysError::setError("ArrayList ERROR: Not enough space.");
  }

  return 0;  // TODO return what!
}

template <class Value>
ArrayListNode<Value>& ArrayList<Value>::operator[](unsigned idx) {
  return (this->values[idx]);
}

template <class Value>
const ArrayListNode<Value>& ArrayList<Value>::operator[](unsigned idx) const {
  return (this->values[idx]);
}

////////////////////////////////////

template <class Value>
class ArrayListTicketedIter;

template <class Value>
struct ArrayListTicketedNode {
  Value v;
  int next;
  Ticket t;
};

template <class Value>
class ArrayListTicketed {
  public:
    ArrayListTicketed(unsigned capacity);
    //ArrayList(const ArrayList< TicketedContent<Value> >& arraylist);

    virtual ~ArrayListTicketed();

    Ticket& insert(Value value);
    //void erase(unsigned index);  // cant be erased directly, the iterator will erase it

    unsigned getCapacity() {return (c);}
    unsigned getSize() {return (s);}

    bool isEmpty() {return (s==0);}

    ArrayListTicketedIter<Value> begin() {return (ArrayListTicketedIter<Value>(this));}
    ArrayListTicketedIter<Value>   end() {return (ArrayListTicketedIter<Value>(this,-1));}

    ArrayListTicketedNode<Value>& operator[](unsigned idx);
    const ArrayListTicketedNode<Value>& operator[](unsigned idx) const;

  private:
    friend class ArrayListTicketedIter<Value>;

    ArrayListTicketedNode<Value> *values;
    int i;
    int f;
    unsigned c;
    unsigned s;
};

template <class Value>
ArrayListTicketed<Value>::ArrayListTicketed(unsigned capacity) : i(-1), f(0), c(capacity), s(0) {
  values = new ArrayListTicketedNode<Value>[capacity];
  for(unsigned i = 0; i < c; i++) {
     values[i].next = i+1;
  }
  values[c-1].next = -1;
}

//template <class Value>
//ArrayList< TicketedContent<Value> >::ArrayList(const ArrayList< TicketedContent<Value> >& arraylist) : i(arraylist.i), f(arraylist.f), c(arraylist.c), s(arraylist.s) {
//printf("ArrayList constructor ticketd.\n");
//  values = new ArrayListNode< TicketedContent<Value> >[c];
//  for(unsigned i = 0; i < c; i++) {
//     values[i].next = i+1;
//  }
//  values[c-1].next = -1;
//  ArrayListIter< TicketedContent<Value> > it = arraylist.begin();
//  for(;it != arraylist.end(); ++it) {
//    this->insert(*it);
//  }
//}

template <class Value>
ArrayListTicketed<Value>::~ArrayListTicketed() {
  delete[] values;
}

template <class Value>
Ticket& ArrayListTicketed<Value>::insert(Value value) {
  if(s < c) {
    values[f].v = value;
    values[f].t.setACTIVE();
    unsigned aux = values[f].next;
    values[f].next = i;
    i = f;
    f = aux;
    s++;
  } else {
    SysError::setError("ArrayListTicketed ERROR: Not enough space.");
  }
  return (values[i].t);
}

template <class Value>
ArrayListTicketedNode<Value>& ArrayListTicketed<Value>::operator[](unsigned idx) {
  return (this->values[idx]);
}

template <class Value>
const ArrayListTicketedNode<Value>& ArrayListTicketed<Value>::operator[](unsigned idx) const {
  return (this->values[idx]);
}









//struct node_base
//{
//    node_base() : m_next(0) {}
//
//    // Each node manages all of its tail nodes
//    virtual ~node_base() { delete m_next; }
//
//    // Access the rest of the list
//    node_base* next() const { return m_next; }
//
//    // print to the stream
//    virtual void print(std::ostream& s) const = 0;
//
//    // double the value
//    virtual void double_me() = 0;
//
//    void append(node_base* p)
//    {
//        if (m_next)
//            m_next->append(p);
//        else
//            m_next = p;
//    }
//
// private:
//    node_base* m_next;
//};
//
//template <class T>
//struct node : node_base
//{
//    node(T x)
//      : m_value(x)
//    {}
//
//    void print(std::ostream& s) const { s << this->m_value; }
//    void double_me() { m_value += m_value; }
//
// private:
//    T m_value;
//};
//
//inline std::ostream& operator<<(std::ostream& s, node_base const& n)
//{
//    n.print(s);
//    return s;
//}

}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_ARRAYLIST_H_
