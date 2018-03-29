/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Behavior.h
 * @since 2014-09-12
 * @date 2018-02-25
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

}  // namespace zbe

#endif  // ZBE_CORE_BEHAVIORS_BEHAVIOR_H_
