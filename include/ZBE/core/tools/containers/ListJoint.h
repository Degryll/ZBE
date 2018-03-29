/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ListJoint.h
 * @since 2017-05-23
 * @date 2018-03-21
 * @author Degryll Ludo Batis
 * @brief A list of lists. When iterated, it will iterate over all contained lists.
 */

#ifndef ZBE_CORE_TOOLS_CONTAINERS_LISTJOINT_H_
#define ZBE_CORE_TOOLS_CONTAINERS_LISTJOINT_H_

#include <forward_list>
#include <iterator>

#include "ZBE/core/tools/containers/TicketedForwardList.h"

namespace zbe {

/** \brief Iterator for Joint container.
 */
template<typename J, typename L, typename E> //!< Joint type, List type, Element type.
class JointIterator : public std::iterator<std::forward_iterator_tag, E>{
public:

  /** \brief parametrized constructor
   *  \param l The joint.
   */
  JointIterator(J *l) : l(l), jit(firstNonEmptyL()), lit(firstElement()) {}

  /** \brief parametrized constructor
   *  \param l The joint.
   *  \param jit Another iterator to build this iterator from it.
   */
  JointIterator(J *l, typename J::iterator jit) : l(l), jit(jit), lit() {}

  /** \brief copy constructor
   */
  JointIterator(const JointIterator& rhs) : l(rhs.l), jit(rhs.jit), lit(rhs.lit) {}

  /** \brief operator =
   */
  JointIterator& operator=(const JointIterator& rhs){
    this->l = rhs.l;
    this->jit = rhs.jit;
    this->lit = rhs.lit;
    return (*this);
  }

  /** \brief operator ++
   */
  JointIterator& operator++() {
    lit++;
    if(lit == (*jit)->end()){
      jit = nextNonEmptyL(++jit);
      if(jit != l->end()){
        lit = (*jit)->begin();
      }
    }
    return (*this);
  }

  /** \brief operator ++
   */
  JointIterator operator++(int) {
      JointIterator pre = (*this);
      (*this)++;
      return (pre);
  }

  /** \brief operator ==
   */
  bool operator==(const JointIterator& rhs) {
    return ((this->l == rhs.l) && (this->jit == rhs.jit) && ((jit==l->end()) || (this->lit == rhs.lit)));
  }

  /** \brief operator !=
   */
  bool operator!=(const JointIterator& rhs){
    return (!((*this)==rhs));
  }

  /** \brief operator *
   */
  E operator*(){
    return (*lit);
  }

  /** \brief operator ->
   */
  E operator->(){
    return (*lit);
  }

private:
  typename J::iterator nextNonEmptyL(typename J::iterator nextJit) {
      while(nextJit != l->end() && (*nextJit)->empty()) ++nextJit;
      return (nextJit);
  }

  typename J::iterator firstNonEmptyL() {
      return (nextNonEmptyL(l->begin()));
  }

  typename L::iterator firstElement() {
      if(jit != l->end()) return ((*jit)->begin());
      else return typename L::iterator();
  }

  J *l;
  typename J::iterator jit;
  typename L::iterator lit;
}; // iterator


/** \brief Collections of lists of element of type T. It can be iterated through
* T elements.
 */
template<typename L, typename T>
class ListJoint {
public:
    /** \brief empty constructor
    */
    ListJoint() : l() {}

    using iterator = JointIterator<std::forward_list<L*>, L, T>;

    /** \brief adds a list to the joint.
     */
    typename std::forward_list<L*>::iterator add(L* list) {
      l.push_front(list);
      return (l.before_begin());
    }

    /** \brief Erases the next element from the list.
     */
    void erase(typename std::forward_list<L*>::iterator erase_it) {
      l.erase_after(erase_it);
    }

    /** \brief Returns an interator refering to the beginning of the list.
     */
    iterator begin(){
      return (iterator(&l));
    }

    /** \brief Returns an interator refering to the end of the list.
     */
    iterator end(){
      return (iterator(&l, l.end()));
    }

private:
  std::forward_list<L*> l;

};

/** \brief Collections of ticketed lists of element of type T. It can be iterated through
* T elements.
 */
template<typename L, typename T>
class ListTicketedJoint {
public:
    /** \brief Empty constructor.
     */
    ListTicketedJoint() : l() {}

    using iterator = JointIterator<TicketedForwardList<L>, L, T>;

    /** \brief Adds an element to the beginning of the list;
     */
    std::shared_ptr<zbe::TicketedElement<L> > add(std::shared_ptr<L> list) {
      return l.push_front(list);
    }

    /** \brief Returns an iterator refering to the first element of the first list.
     */
    iterator begin(){
      return (iterator(&l));
    }

    /** \brief Returns an iterator refering to the end of the list.
     */
    iterator end(){
      return (iterator(&l, l.end()));
    }

private:
  TicketedForwardList<L> l;

};

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_LISTJOINT_H_
