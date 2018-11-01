/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Bounce.h
 * @since 2017-01-13
 * @date 2017-05-10
 * @author Degryll Ludo
 * @brief Implements a bounce behavior.
 */

#ifndef ZBE_BEHAVIORS_BOUNCE_H_
#define ZBE_BEHAVIORS_BOUNCE_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Bouncer.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Implements a bounce behavior.
 */
template<unsigned s>
class Bounce : virtual public Behavior<Bouncer<s>  > {
  public:

    /** \brief Virtual destructor.
     */
    virtual ~Bounce() {}

    /** \brief Changes the entity velocity with the accumulated normals.
     */
    void apply(std::shared_ptr<AvatarEntityContainer<Bouncer<s> > > aec) {
      Bouncer<s>* avatar;
      assignAvatar(aec, &avatar);
      if(avatar->hasNormals()){
        avatar->setVelocity(avatar->getVelocity().reflect(avatar->getNormalSum()));
        avatar->clearNormals();
      }
    }
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_BOUNCE_H_
