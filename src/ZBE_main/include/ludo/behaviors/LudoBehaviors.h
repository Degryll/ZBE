/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoHandlers.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Collection of zbe::InputHandler && zbe::TimeHandler for ludomain.
 */
#ifndef LUDO_EVENTS_HANDLERS_LUDOBEHAVIORS_H
#define LUDO_EVENTS_HANDLERS_LUDOBEHAVIORS_H

#include <cstdio>

#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"

#include "ZBE/entities/avatars/Movable.h"

namespace ludo {

/** \brief Implements a bounce behavior.
 */
template<unsigned s>
class Rotator : public zbe::Behavior<zbe::Movable<s> > {
  public:
    Rotator(double angle): a(angle){}
    virtual ~Rotator() {}

    void apply(zbe::AvatarEntity<zbe::Movable<s> >* entity, int64_t) {
      zbe::Movable<s>* avatar;
      entity->assignAvatar(&avatar);
      zbe::Vector<s>& v = avatar->getVelocity();
      double rads = v.getRads();
      double mod = v.getModule();
      double vx = sin(rads+a)*mod;
      double vy = cos(rads+a)*mod;
      v[0] = vx;
      v[1] = vy;
      avatar->setVelocity(v);
    }

  private:
    double a;
};

} //namespace ludo

#endif //LUDO_EVENTS_HANDLERS_LUDOBEHAVIORS_H
