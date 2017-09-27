/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Behavior.h
 * @since 2014-09-12
 * @date 2017-09-12
 * @author Ludo and Degryll
 * @brief Define the minimal functions of every behavior.
 */

#ifndef ZBE_CORE_BEHAVIORS_BEHAVIOR_H_
#define ZBE_CORE_BEHAVIORS_BEHAVIOR_H_

#include <memory>

#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

/** \brief Define the minimal functions of every behavior.
 */
template<typename ...Avatars>
class Behavior {
public:
  /** \brief Virtual destructor.
   */
  virtual ~Behavior() {}

  /** \brief Do the behavior work over the given entity
   *  \param entity The entity to behave.
   */
  virtual void apply(std::shared_ptr<AvatarEntityContainer<Avatars...> > aec) = 0;

};

//template <typename T, typename ...Avatars>
//void apply(Behavior<Avatars...> *b, std::shared_ptr<T> thing) {
//  AvatarEntityContainer<Avatars...>* aec;
//  wrapAEC(&aec, thing);
//  b->apply(aec);
//  delete aec;
//};

}  // namespace zbe

#endif  // ZBE_CORE_BEHAVIORS_BEHAVIOR_H_
