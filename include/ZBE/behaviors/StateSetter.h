/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StateSetter.h
 * @since 2018-01-08
 * @date 2018-01-08
 * @author Degryll Ludo Bates
 * @brief Sets a given state to the entity.
 */

#ifndef ZBE_BEHAVIORS_STATESETTER_H_
#define ZBE_BEHAVIORS_STATESETTER_H_

#include <memory>
#include <cstdint>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Stated.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Sets a given state to the entity.
 */
class StateSetter : virtual public Behavior<Stated> {
public:

  StateSetter(uint64_t state) : state(state) {}

  /** \brief Virtual destructor.
   */
  virtual ~StateSetter() {}

  /** \brief Sets the entity state to given one.
   */
  void apply(std::shared_ptr<AvatarEntityContainer<Stated> > aecs) {
    zbe::Stated* stated;
    assignAvatar(aecs , &stated);
    stated->setState(state);
  }

private:
  uint64_t state;
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_STATESETTER_H_
