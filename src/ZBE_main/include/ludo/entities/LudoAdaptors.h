/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoEntities.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Entities for ludo's proving grounds.
 */

#ifndef ZBE_MAIN_LUDO_ENTITIES_LUDOADAPTORS
#define ZBE_MAIN_LUDO_ENTITIES_LUDOADAPTORS

#include <cstdint>
#include <memory>

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/RotatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleRotatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleAnimatedSprite.h"

#include "ludo/entities/LudoAvatars.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/archetypes/LudoArchetypes.h"

namespace ludo {

class RotatedDrawableSimpleRotatedSpriteAdaptor : public zbe::Adaptor<zbe::RotatedSprite> {
public:
  RotatedDrawableSimpleRotatedSpriteAdaptor(const RotatedDrawableSimpleRotatedSpriteAdaptor&) = delete;
  void operator=(const RotatedDrawableSimpleRotatedSpriteAdaptor&) = delete;

  RotatedDrawableSimpleRotatedSpriteAdaptor(std::weak_ptr<RotatedDrawable> archetype):a(archetype), s(nullptr){}

  ~RotatedDrawableSimpleRotatedSpriteAdaptor() {delete s;}

  zbe::RotatedSprite* getAvatar() {
    delete s;
    std::shared_ptr<RotatedDrawable> archetype = a.lock();
    double angle = (archetype->getAngle() < 0 ? 360.0 + archetype->getAngle() : archetype->getAngle());
    s = new zbe::SimpleRotatedSprite(archetype->getX(), archetype->getY(), archetype->getW(), archetype->getH(),archetype->getGraphics(), angle);
    return (s);
  };

private:
  std::weak_ptr<RotatedDrawable> a;
  zbe::RotatedSprite* s;
};

/** \brief Adapts a Ludoball to a Collisionator.
 */
template <typename R>
class LudoBallCollisionatorAdaptor : public zbe::Adaptor<zbe::Collisionator<R> > {
public:
  LudoBallCollisionatorAdaptor(const LudoBallCollisionatorAdaptor&) = delete;
  void operator=(const LudoBallCollisionatorAdaptor&) = delete;

  LudoBallCollisionatorAdaptor(std::weak_ptr<LudoBall<R> > ball): b(ball), c(nullptr) {
      std::shared_ptr<LudoBall<R> > initialBall = b.lock();
      std::shared_ptr<zbe::CollisionObject<R> > co = std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::ConstantMovingCircle<R>(zbe::Circle(initialBall->getPosition(), initialBall->getWidth()), initialBall->getVelocity()));
      std::shared_ptr<zbe::ReactObject<R> > ro = std::make_shared<zbe::ReactObjectCommon<R> >();
      c = new zbe::CollisionatorCommon<R, zbe::Avatar, zbe::Bouncer<2> >(std::make_shared<zbe::WeakAvatarEntityContainer<zbe::Avatar, zbe::Bouncer<2> > >(initialBall), co, ro, initialBall->getActuatorsList() ,initialBall->getCollisionablesList());

  }

  ~LudoBallCollisionatorAdaptor() {delete c;}

  zbe::Collisionator<R>* getAvatar() {
      std::shared_ptr<LudoBall<R> > ball = b.lock();
      std::shared_ptr<zbe::CollisionObject<R> > co = std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::ConstantMovingCircle<R>(zbe::Circle(ball->getPosition(), ball->getWidth()), ball->getVelocity()));
      std::shared_ptr<zbe::ReactObject<R> > ro = std::make_shared<zbe::ReactObjectCommon<R> >();
      c->setCollisionObject(co);
      c->setReactObject(ro);
      return (c);
    }

private:
	std::weak_ptr<LudoBall<R> > b;
	zbe::CollisionatorCommon<R, zbe::Avatar, zbe::Bouncer<2> >* c;
};

class BallParticleAnimatedSpriteAdaptor : public zbe::Adaptor<zbe::AnimatedSprite>{

  BallParticleAnimatedSpriteAdaptor(const BallParticleAnimatedSpriteAdaptor&) = delete;
  void operator=(const BallParticleAnimatedSpriteAdaptor&) = delete;

  public:
    BallParticleAnimatedSpriteAdaptor(std::weak_ptr<BallParticle> ballParticle) : bp(ballParticle), as(nullptr), sysTime(zbe::SysTime::getInstance()) {
      std::shared_ptr<BallParticle> p = ballParticle.lock();
      as = new zbe::SimpleAnimatedSprite(p->getX(), p->getY(), p->getW(), p->getH(), p->getGraphics(), p->getAngle(), p->getState(), 0);
    }

    ~BallParticleAnimatedSpriteAdaptor(){delete as;}

    zbe::AnimatedSprite* getAvatar() {
        delete as;
        std::shared_ptr<BallParticle> p = bp.lock();
        as = new zbe::SimpleAnimatedSprite(p->getX(), p->getY(), p->getW(), p->getH(), p->getGraphics(), p->getAngle(), p->getState(), sysTime.getTotalTime());
        return as;
    }

  private:
    std::weak_ptr<BallParticle> bp;
    zbe::SimpleAnimatedSprite* as;
    zbe::SysTime &sysTime;
};

class GraphicElementAnimatedSpriteAdaptor : public zbe::Adaptor<zbe::AnimatedSprite>{

  GraphicElementAnimatedSpriteAdaptor(const GraphicElementAnimatedSpriteAdaptor&) = delete;
  void operator=(const GraphicElementAnimatedSpriteAdaptor&) = delete;

  public:
    GraphicElementAnimatedSpriteAdaptor(std::weak_ptr<GraphicElement> graphElem) : ge(graphElem), as(nullptr), sysTime(zbe::SysTime::getInstance()) {
      std::shared_ptr<GraphicElement> g = graphElem.lock();
      as = new zbe::SimpleAnimatedSprite(g->getX(), g->getY(), g->getW(), g->getH(), g->getGraphics(), g->getAngle(), g->getState(), sysTime.getTotalTime() - g->getTimeStamp());
    }

    ~GraphicElementAnimatedSpriteAdaptor(){delete as;}

    zbe::AnimatedSprite* getAvatar() {
        delete as;
        std::shared_ptr<GraphicElement> g = ge.lock();
        as = new zbe::SimpleAnimatedSprite(g->getX(), g->getY(), g->getW(), g->getH(), g->getGraphics(), g->getAngle(), g->getState(), sysTime.getTotalTime() - g->getTimeStamp());
        return as;
    }

  private:
    std::weak_ptr<GraphicElement> ge;
    zbe::SimpleAnimatedSprite* as;
    zbe::SysTime &sysTime;
};

} // namespace

#endif //ZBE_MAIN_LUDO_ENTITIES_LUDOADAPTORS
