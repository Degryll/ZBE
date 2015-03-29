/**
 * Copyright 2011 Batis Degryll Ludo
 * @file arrayList.h
 * @since 2015/02/08
 * @date 2015/02/08
 * @author Degryll
 * @brief A list in an static array.
 */

#ifndef CORE_TOOLS_CONTAINERS_ARRAYLIST_H_
#define CORE_TOOLS_CONTAINERS_ARRAYLIST_H_

#include <iostream>

namespace zbe {

template <class Value>
class ArrayListIter;

template <class Value>
struct ArrayListNode {
  Value value;
  unsigned next;
};

template <class Value>
class ArrayList {
  public:
    ArrayList(unsigned capacity);
    ArrayList(const ArrayList<Value>& arraylist);

    virtual ~ArrayList();

    unsigned insert(Value value);
    void erase(unsigned index);

    unsigned getCapacity() {return (c);}
    unsigned getSize() {return (s);}

    bool isEmpty() {return (s==0);}

    ArrayListIter<Value> begin() {return (ArrayListIter<Value>(this));}
    ArrayListIter<Value> end() {return (ArrayListIter<Value>(this,-1));}

    arrayListNode<Value>& operator[](unsigned idx);
    const arrayListNode<Value>& operator[](unsigned idx) const;

  private:
    ArrayListNode<Value> *values;
    // [TODO] Index of free, no index of ocupied (each element has his ticket)
    // no iterator, change name
    unsigned i;
    unsigned f;
    unsigned c;
    unsigned s;
};

template <class Value>
ArrayList<Value>::ArrayList<Value>(unsigned capacity) : i(-1), f(0), c(capacity), s(0) {
  values = new ArrayListNode<Value>[capacity];
  for(unsigned i = 0; i < c; i++) {
     values[i].next = i+1;
  }
  values[c-1].next = -1;
}

template <class Value>
ArrayList<Value>::ArrayList<Value>(const ArrayList<Value>& arraylist) : i(arraylist.i), f(arraylist.f), c(arraylist.c), s(arraylist.s) {
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
  } // else error not enough space
}

template <class Value>
void ArrayList<Value>::erase(unsigned index) {

}

template <class Value>
arrayListNode<Value>& ArrayList<Value>::operator[](unsigned idx) {
  return (this->values[idx])
}

template <class Value>
const arrayListNode<Value>& ArrayList<Value>::operator[](unsigned idx) const {
  return (this->values[idx])
}

struct node_base
{
    node_base() : m_next(0) {}

    // Each node manages all of its tail nodes
    virtual ~node_base() { delete m_next; }

    // Access the rest of the list
    node_base* next() const { return m_next; }

    // print to the stream
    virtual void print(std::ostream& s) const = 0;

    // double the value
    virtual void double_me() = 0;

    void append(node_base* p)
    {
        if (m_next)
            m_next->append(p);
        else
            m_next = p;
    }

 private:
    node_base* m_next;
};

template <class T>
struct node : node_base
{
    node(T x)
      : m_value(x)
    {}

    void print(std::ostream& s) const { s << this->m_value; }
    void double_me() { m_value += m_value; }

 private:
    T m_value;
};

inline std::ostream& operator<<(std::ostream& s, node_base const& n)
{
    n.print(s);
    return s;
}

}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_ARRAYLIST_H_
