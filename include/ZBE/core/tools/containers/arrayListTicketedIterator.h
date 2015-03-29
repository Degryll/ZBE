/**
 * Copyright 2011 Batis Degryll Ludo
 * @file arrayListIterator.h
 * @since 2015/02/08
 * @date 2015/02/08
 * @author Degryll
 * @brief A ticketed iterator for the arrayList.
 */

#ifndef CORE_TOOLS_CONTAINERS_ARRAYLISTTICKETEDITERATOR_H_
#define CORE_TOOLS_CONTAINERS_ARRAYLISTTICKETEDITERATOR_H_

#include "arrayList.h"
#include <boost/iterator/iterator_facade.hpp>

namespace zbe {

template <class Value>
class node_iter_ticketed
  : public boost::iterator_facade<
        node_iter_ticketed<ticketedContent<Value>>
      , Value
      , boost::forward_traversal_tag
    >
{
 public:
    node_iter_ticketed()
      : m_node(0) {}

    explicit node_iter_ticketed(Value* p)
      : m_node(p) {}

 private:
    friend class boost::iterator_core_access;

    bool equal(node_iter_ticketed<Value> const& other) const
    {
        return this->m_node == other.m_node;
    }

    void increment()
    { m_node = m_node->next(); }

    Value& dereference() const
    { return *m_node; }

    Value* m_node;
};


}  // namespace zbe

#endif  // CORE_TOOLS_CONTAINERS_ARRAYLISTTICKETEDITERATOR_H_
