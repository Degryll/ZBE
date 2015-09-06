/**
 * Copyright 2011 Batis Degryll Ludo
 * @file arrayListIterator.h
 * @since 2015/02/08
 * @date 2015/04/10
 * @author Degryll
 * @brief An iterator for the arrayList.
 */

#ifndef CORE_TOOLS_CONTAINERS_ARRAYLISTITERATOR_H_
#define CORE_TOOLS_CONTAINERS_ARRAYLISTITERATOR_H_

#include <cstdio>

#include <boost/iterator/iterator_facade.hpp>

#include "arrayList.h"
#include "Ticket.h"

namespace zbe {

template <class Value>
struct ArrayListNode;

template <class Value>
class ArrayList;

template <class Value>
class ArrayListIter
  : public boost::iterator_facade<
        ArrayListIter<Value>
      , Value
      , boost::forward_traversal_tag> {

public:

  ArrayListIter() : l(0), i(-1) {}
  ArrayListIter(ArrayList<Value> *list) : l(list), i(list->getIndex()) {}
  ArrayListIter(ArrayList<Value> *list, unsigned i) : l(list), i(i) {}
  ArrayListIter(const ArrayListIter<Value>& iter) : l(iter.l), i(iter.i) {}

  virtual ~ArrayListIter() {}

  private:
    friend class boost::iterator_core_access;

    bool equal(ArrayListIter<Value> const& other) const {
        return (this->l == other.l &&
                this->i == other.i);
    }

    void increment() {
      i = (*l)[i].next;
    }

    Value& dereference() const {
      return ((*l)[i].value);
    }

    ArrayList<Value> *l;
    unsigned i;
};

template <typename T>
using ArrayListIterator = ArrayListIter<T>;
template <typename T>
using ArrayListConstIterator = ArrayListIter<T const>;

////////////////////////////////////

template <class Value>
struct ArrayListTicketedNode;

template <class Value>
class ArrayListTicketed;

template <class Value>
class ArrayListTicketedIter
  : public boost::iterator_facade<
        ArrayListTicketedIter<Value>
      , Value
      , boost::forward_traversal_tag> {

public:

  ArrayListTicketedIter() : l(0), i(-1) {}
  ArrayListTicketedIter(ArrayListTicketed<Value> *list) : l(list), i(list->i) {}
  ArrayListTicketedIter(ArrayListTicketed<Value> *list, unsigned i) : l(list), i(i) {}
  ArrayListTicketedIter(const ArrayListTicketedIter<Value>& iter) : l(iter.l), i(iter.i) {}

  virtual ~ArrayListTicketedIter() {}


// que hace? para que?
  void reset() {
    i = l->i;
    if ((i != -1) && ((*l)[i].t.isNOTACTIVE())) {
      increment();
    }
  }

  // TODO Degryll Añadir operator=

  private:
    friend class boost::iterator_core_access;

    bool equal(ArrayListTicketedIter<Value> const& other) const {
        return (this->l == other.l &&
                this->i == other.i);
    }

    void increment() {
      int aux = (*l)[i].next;
      while((aux != -1) && ((*l)[aux].t.isNOTACTIVE())) {
        if((*l)[aux].t.isERASED()) {
          int aux2  = (*l)[aux].next;
          (*l)[i].next = aux2;
          ((*l)[aux]).next = l->f;
          l->f = aux;
          aux = aux2;
        } else {
          i = aux;  // avoid bug in line (*l)[i].next = aux2;
          aux = (*l)[aux].next;
        }
      }
      i = aux;
    }

     Value& dereference() const {
      return ((*l)[i].v);
    }

    ArrayListTicketed<Value> *l;
    int i;
};

template <typename T>
using ArrayListTicketedIterator = ArrayListTicketedIter<T>;
template <typename T>
using ArrayListTicketedConstIterator = ArrayListTicketedIter<T const>;

}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_ARRAYLISTITERATOR_H_
