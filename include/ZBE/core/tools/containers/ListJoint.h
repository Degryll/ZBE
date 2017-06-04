/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ListJoint.h
 * @since 2017/05/23
 * @date 2017/05/23
 * @author Degryll Ludo Batis
 * @brief A list of lists. When iterated, it will iterate over all contained lists.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_LISTJOINT_H_
#define ZBE_CORE_TOOLS_CONTAINERS_LISTJOINT_H_

#include <forward_list>

#include "ZBE/core/tools/containers/TicketedForwardList.h"

namespace zbe {

template<typename J, typename L, typename E> //!< Joint type, List type, Element type.
class JointIterator : public std::iterator<std::forward_iterator_tag, E>{
public:

  JointIterator(J *l) : l(l), jit(l->begin()), lit((*jit)->begin()) {}
  JointIterator(J *l, typename J::iterator jit) : l(l), jit(jit), lit() {}
  JointIterator(J *l, typename J::iterator jit, typename  L::iterator lit) : l(l), jit(jit), lit(lit) {}
  JointIterator(const JointIterator& rhs) : l(rhs.l), jit(rhs.jit), lit(rhs.lit) {}

  JointIterator& operator=(const JointIterator& rhs){
    this->l = rhs.l;
    this->jit = rhs.jit;
    this->lit = rhs.lit;
    return (*this);
  }

  JointIterator& operator++() {
    lit++;
    if(lit == (*jit)->end()){
      jit++;
      if(jit != l->end()){
        lit = (*jit)->begin();
      }
    }
    return (*this);
  }

  JointIterator operator++(int) {
      JointIterator pre = (*this);
      (*this)++;
      return (pre);
  }

  bool operator==(const JointIterator& rhs) {
    return ((this->l == rhs.l) && (this->jit == rhs.jit) && ((jit==l->end()) || (this->lit == rhs.lit)));
  }

  bool operator!=(const JointIterator& rhs){
    return (!((*this)==rhs));
  }

  E operator*(){
    return (*lit);
  }

  E operator->(){
    return (*lit);
  }

private:
  J *l;
  typename J::iterator jit;
  typename L::iterator lit;
}; // iterator


template<typename L, typename T>
class ListJoint {
public:

    ListJoint() : l() {}

    using iterator = JointIterator<std::forward_list<L*>, L, T>;

    typename std::forward_list<L*>::iterator add(L* list) {
      l.push_front(list);
      return (l.before_begin());
    }

    void erase(typename std::forward_list<L*>::iterator erase_it) {
      l.erase_after(erase_it);
    }

    iterator begin(){
      return (iterator(&l));
    }

    iterator end(){
      return (iterator(&l, l.end()));
    }

private:
  std::forward_list<L*> l;

};

template<typename L, typename T>
class ListTicketedJoint {
public:

    ListTicketedJoint() : l() {}

    using iterator = JointIterator<TicketedForwardList<L>, L, T>;

    std::shared_ptr<zbe::TicketedElement<L> > add(std::shared_ptr<L> list) {
      return l.push_front(list);
    }

    iterator begin(){
      return (iterator(&l));
    }

    iterator end(){
      return (iterator(&l, l.end()));
    }

private:
  TicketedForwardList<L> l;

};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_LISTJOINT_H_
