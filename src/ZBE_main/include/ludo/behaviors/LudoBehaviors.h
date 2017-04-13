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
#include <memory>

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/containers/ListManager.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/AvatarEntity.h"


#include "ZBE/entities/avatars/Movable.h"

#include "ludo/events/handlers/LudoHandlers.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/entities/LudoAdaptors.h"
#include "ludo/archetypes/LudoArchetypes.h"

namespace ludo {

/** \brief Implements a rotator behavior for a Movable.
 */
class Rotator : public zbe::Behavior<zbe::Movable<2> > {
  public:
    Rotator(double angle): a(angle){}
    virtual ~Rotator() {}

    void apply(std::shared_ptr<zbe::AvatarEntity<zbe::Movable<2> > > entity, int64_t) {
      zbe::Movable<2>* avatar;
      entity->assignAvatar(&avatar);
      zbe::Vector<2>& v = avatar->getVelocity();
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

/** \brief Implements a behavior for a Movable that builds BallParticles.
 */
class BackBallParticlesLauncher : public zbe::Behavior<zbe::Movable<2> > {
  public:
    BackBallParticlesLauncher(const BackBallParticlesLauncher&) = delete;
    void operator=(const BackBallParticlesLauncher&) = delete;

    BackBallParticlesLauncher(double radius, uint64_t graphics, uint64_t spriteList, zbe::TimeEventGenerator* teg) :
        r(radius), g(graphics), sList(spriteList), teg(teg), store(zbe::EventStore::getInstance()) {
    }

    virtual ~BackBallParticlesLauncher() {}

    void apply(std::shared_ptr<zbe::AvatarEntity<zbe::Movable<2> > > entity, int64_t) {
      zbe::Movable<2>* avatar;
      entity->assignAvatar(&avatar);
      zbe::Vector<2>& v = avatar->getVelocity();
      zbe::Point<2>& p = avatar->getPosition();
      double rads = v.getRads();
      rads += zbe::PI;
      std::shared_ptr<BallParticle> bp = std::make_shared<BallParticle>(p[0], p[1], r, g, rads * zbe::TODEGREE);
      std::shared_ptr<zbe::Adaptor<SimpleRotatedSprite> > sAdaptor = std::make_shared<RotatedDrawableSimpleRotatedSpriteAdaptor>(&(*bp));
      zbe::setAdaptor(bp, sAdaptor);
      auto ticket = zbe::ListManager<zbe::TicketedForwardList<zbe::AvatarEntity<SimpleRotatedSprite> > >::getInstance().get(sList)->push_front(bp);
      std::shared_ptr<zbe::TimeHandler> eraser = std::make_shared<TicketEraser>(ticket);
      teg->addTimer(eraser, store.getTime() + zbe::SECOND/4);
    }

  private:
    double r;
    uint64_t g;
    uint64_t sList;
    zbe::TimeEventGenerator* teg;
    zbe::EventStore& store;
};

} //namespace ludo

#endif //LUDO_EVENTS_HANDLERS_LUDOBEHAVIORS_H