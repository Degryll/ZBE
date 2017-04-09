/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Bounce.h
 * @since 2017-01-13
 * @date 2017-01-13
 * @author Degryll
 * @brief Implements a bounce behavior.
 */

#ifndef ZBE_BEHAVIORS_BOUNCE_H_
#define ZBE_BEHAVIORS_BOUNCE_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/entities/AvatarEntity.h"

namespace zbe {

/** \brief Implements a bounce behavior.
 */
template<unsigned s>
class Bounce : public Behavior<Bouncer<s>  > {
  public:

    /** \brief Default destructor.
     */
    virtual ~Bounce() {}

    /** \brief Do the behavior work over the given entity
     */
    void apply(std::shared_ptr<AvatarEntity<Bouncer<s> > > entity, int64_t) {
      Bouncer<s>* avatar;
      entity->assignAvatar(&avatar);
      if(avatar->hasNormals()){
      	avatar->setVelocity(avatar->getVelocity().reflect(avatar->getNormalSum()));
      	avatar->clearNormals();
      }
    }
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_BOUNCE_H_
