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

namespace zbe {
template<typename L, typename T>
class ListJoint {
public:

    class iterator : public std::iterator<std::forward_iterator_tag, T>{
    public:
      iterator(std::forward_list<L*> *l) : l(l), it(l->begin()), lit((*it)->begin()) {}
      iterator(std::forward_list<L*> *l, typename std::forward_list<L*>::iterator it) : l(l), it(it), lit() {}
      iterator(std::forward_list<L*> *l, typename std::forward_list<L*>::iterator it, typename  L::iterator lit) : l(l), it(it), lit(lit) {}
      iterator(const iterator& rhs) : l(rhs.l), it(rhs.it), lit(rhs.lit) {}

      iterator& operator=(const iterator& rhs){
        this->l=rhs.l;
        this->it=rhs.it;
        this->lit=rhs.lit;
        return (*this);
      }

      iterator& operator++() {
        lit++;
        if(lit == (*it)->end()){
          it++;
          if(it != l->end()){
            lit = (*it)->begin();
          }
        }
        return (*this);
      }

      iterator operator++(int) {
          iterator pre = (*this);
          (*this)++;
          return (pre);
      }

      bool operator==(const iterator& rhs) {
        return ((this->l == rhs.l) && (this->it == rhs.it) && ((it==l->end()) || (this->lit == rhs.lit)));
      }

      bool operator!=(const iterator& rhs){
        return (!((*this)==rhs));
      }

      T& operator*(){
        return (*lit);
      }

      T& operator->(){
        return (*lit);
      }

    private:
      std::forward_list<L*> *l;
      typename std::forward_list<L*>::iterator it;
      typename L::iterator lit;
    }; // iterator

    ListJoint():l(){}

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

}  // namespace zbe

#endif  // ZBE_CORE_TOOLS_CONTAINERS_LISTJOINT_H_
