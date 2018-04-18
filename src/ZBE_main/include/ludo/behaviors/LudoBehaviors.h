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
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/events/generators/TimeEventGenerator.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/RotatedSprite.h"


#include "ZBE/entities/avatars/Movable.h"

#include "ludo/events/handlers/LudoHandlers.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/entities/LudoAdaptors.h"
#include "ludo/archetypes/LudoArchetypes.h"

namespace ludo {

/** \brief Behavior that runs a daemon for any kind of avatar.
 */
template<typename T>
class DaemonRunnerBehavior : public zbe::Behavior<T> {
public:
    DaemonRunnerBehavior(zbe::Daemon* daemon): d(daemon){}
    ~DaemonRunnerBehavior(){delete d;}
    void apply(std::shared_ptr<zbe::AvatarEntity<T> >){
        d->run();
    }
private:
  zbe::Daemon* d;
};

/** \brief Implements a behavior for a Positionable that build circle areas.
 */
template<typename R>
class DestroyerCircleAreaCreator : public zbe::Behavior<zbe::Positionable<2> > {
public:
  DestroyerCircleAreaCreator(double radius, uint64_t catorListId, uint64_t conerListId, uint64_t actuatorsList)
    : lmAEC(zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >::getInstance()),
      aeDestroyer(new zbe::AvatarEntityFixed<Destroyer>(new Destroyer())),
      weakAEC(new zbe::WeakAvatarEntityContainer<Destroyer>(aeDestroyer)),
      ro(new zbe::ReactObjectCommon<R, Destroyer>(weakAEC)),r(radius),ctLId(catorListId), cnLId(conerListId), aLId(actuatorsList) {
  }

  void apply(std::shared_ptr<zbe::AvatarEntityContainer<zbe::Positionable<2> > > entity){
    zbe::Positionable<2>* a;
    assignAvatar(entity, &a);
    //double x, double y, double radius, uint64_t actuatorsList, uint64_t collisionablesList, std::shared_ptr<zbe::ReactObject<R> > ro
    std::shared_ptr<LudoCircleArea<R> > lca(new LudoCircleArea<R>(a->getPosition().x, a->getPosition().y, r, aLId, cnLId, ro));
    lmAEC.get(ctLId)->push_front(lca);
  }
private:
    zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntity<zbe::Collisionator<R> > > >& lmAEC;
    std::shared_ptr<zbe::AvatarEntity<Destroyer> > aeDestroyer;
    std::shared_ptr<zbe::WeakAvatarEntityContainer<Destroyer> > weakAEC;
    std::shared_ptr<zbe::ReactObject<R> > ro;
    double r;
    uint64_t ctLId;
    uint64_t cnLId;
    uint64_t aLId;

};

/** \brief Implements a rotator behavior for a Movable.
 */
class Rotator : public zbe::Behavior<zbe::Movable<2> > {
  public:
    Rotator(double angle): a(angle){}
    virtual ~Rotator() {}

    void apply(std::shared_ptr<zbe::AvatarEntityContainer<zbe::Movable<2> > > entity) {
      zbe::Movable<2>* avatar;
      assignAvatar(entity, &avatar);
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

    BackBallParticlesLauncher(double radius, uint64_t graphics, uint64_t spriteList, std::shared_ptr<zbe::TimeEventGenerator> teg)
        : r(radius), g(graphics), sList(spriteList),
          lmAESRS(zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::RotatedSprite> > >::getInstance()),
          teg(teg), store(zbe::EventStore::getInstance()) {
    }

    virtual ~BackBallParticlesLauncher() {}

    void apply(std::shared_ptr<zbe::AvatarEntityContainer<zbe::Movable<2> > > entity) {
      zbe::Movable<2>* avatar;
      assignAvatar(entity, &avatar);
      zbe::Vector<2>& v = avatar->getVelocity();
      zbe::Point<2>& p = avatar->getPosition();
      double rads = v.getRads();
      rads += zbe::PI;
      std::shared_ptr<BallParticle> bp = std::make_shared<BallParticle>(p[0], p[1], r, g, rads * zbe::TODEGREE);
      std::shared_ptr<zbe::Adaptor<zbe::RotatedSprite> > sAdaptor = std::make_shared<RotatedDrawableSimpleRotatedSpriteAdaptor>(bp);
      zbe::setAdaptor(bp, sAdaptor);
      std::shared_ptr<zbe::AvatarEntityContainer<zbe::RotatedSprite> > aecrs;
      zbe::wrapAEC(&aecrs, bp);
      auto ticket = lmAESRS.get(sList)->push_front(aecrs);
      std::shared_ptr<zbe::TimeHandler> eraser = std::make_shared<TicketEraser>(ticket);
      teg->addTimer(eraser, store.getTime() + zbe::SECOND/4);
    }

  private:
    double r;
    uint64_t g;
    uint64_t sList;
    zbe::RsrcStore<zbe::TicketedForwardList<zbe::AvatarEntityContainer<zbe::RotatedSprite> > >& lmAESRS;
    std::shared_ptr<zbe::TimeEventGenerator> teg;
    zbe::EventStore& store;
};

} //namespace ludo

#endif //LUDO_EVENTS_HANDLERS_LUDOBEHAVIORS_H
