/**
 * Copyright 2011 Batis Degryll Ludo
 * @file arrayListIterator.h
 * @since 2015/02/08
 * @date 2015/02/08
 * @author Degryll
 * @brief An iterator for the arrayList.
 */

#ifndef CORE_TOOLS_CONTAINERS_ARRAYLISTITERATOR_H_
#define CORE_TOOLS_CONTAINERS_ARRAYLISTITERATOR_H_

#include "arrayList.h"
#include <boost/iterator/iterator_facade.hpp>
#include "ticketedContent.h"

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

  ArrayListIter() : l(0), i(-1) {}
  ArrayListIter(ArrayList<Value> *list) : l(list), i(list->i) {}
  ArrayListIter(ArrayList<Value> *list, unsigned i) : l(list), i(i) {}
  ArrayListIter(const ArrayListIter& iter) : l(iter.l), i(iter.i) {}

  virtual ~ArrayListIter() {}

  private:
    friend class boost::iterator_core_access;

    bool equal(ArrayListIter<Value> const& other) const {
        return (this->l == other.l &&
                this->i == other.i);
    }

    void increment() {
      i = l[i].next();
    }

    Value& dereference() const {
      return (l[i].value);
    }

    ArrayList<Value> *l;
    unsigned i;
};
template <class Value>
typedef ArrayListIter<Value> ArrayListIterator;
template <class Value>
typedef ArrayListIter<Value const> ArrayListConstIterator;

}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_ARRAYLISTITERATOR_H_
