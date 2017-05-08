/**
 * Copyright 2012 Batis Degryll Ludo
 * @file UniformLinearMotion.h
 * @since 2017-01-13
 * @date 2017-05-08
 * @author Degryll Ludo
 * @brief Implements an uniform linear motion behavior.
 */

#ifndef ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_
#define ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/system/SysTime.h"

#include "ZBE/entities/avatars/Movable.h"

namespace zbe {

/** \brief Define the minimal functions of every behavior.
 */
template<unsigned s>
class UniformLinearMotion : public Behavior<Movable<s>  > {
  public:
    UniformLinearMotion(const UniformLinearMotion&) = delete;
    void operator=(const UniformLinearMotion&) = delete;

    UniformLinearMotion() : sysTime(zbe::SysTime::getInstance()) {}

    /** \brief Default destructor.
     */
    virtual ~UniformLinearMotion() {}

    /** \brief Do the behavior work over the given entity
     */
    void apply(std::shared_ptr<AvatarEntity<Movable<s> > > entity) {
      Movable<s>* avatar;
      entity->assignAvatar(&avatar);
      Point<s>& p = avatar->getPosition();
      p += (avatar->getVelocity() * sysTime.getCurrentTime()) * zbe::INVERSE_SECOND;
    }

  private:
    zbe::SysTime &sysTime;
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_
