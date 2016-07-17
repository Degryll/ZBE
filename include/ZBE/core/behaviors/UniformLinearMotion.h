/**
 * Copyright 2012 Batis Degryll Ludo
 * @file UniformLinearMotion.h
 * @since 2015-05-04
 * @date 2015-05-04
 * @author Degryll
 * @brief Updates the position of an object based on its speed.
 *        Requires Movible.
 */

#ifndef CORE_BEHAVIORS_UNIFORMLINEARMOTION_H_
#define CORE_BEHAVIORS_UNIFORMLINEARMOTION_H_

#include "any_iterator.hpp"

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/archetypes/Movable.h"

namespace zbe {
template <unsigned s>
class UniformLinearMotion : private Behavior<Movable<s> > {
  virtual void behave(Movable<s> * entity);
};
  /*

//typedef IteratorTypeErasure::any_iterator<
//    //degrill cuidadin cuidadin!! 2 en el movable.
//    Movable<2>, // value type
//    boost::forward_traversal_tag, // traversal tag. Note: std iterator categories are supported here
//    Movable<2>&, // reference type
//    ptrdiff_t // difference type is irrelevant here, just don't use void, that'll throw the iterator_adaptor for a loop
//  > MovableIterator;

template <unsigned s>
using MovableIterator = IteratorTypeErasure::any_iterator<
                          Movable<s>, // value type
                          boost::forward_traversal_tag, // traversal tag. Note: std iterator categories are supported here
                          Movable<s>&, // reference type
                          ptrdiff_t // difference type is irrelevant here, just don't use void, that'll throw the iterator_adaptor for a loop
                        >;

template <unsigned s>
class UniformLinearMotion : private Behavior {
  public:
    ~UniformLinearMotion() {}

    void behaveUntil(double time);

  private:
    MovableIterator<s> first;
    MovableIterator<s> last;
};

*/}  // namespace zbe

#endif  // CORE_BEHAVIORS_UNIFORMLINEARMOTION_H_
