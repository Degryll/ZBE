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

#include "ZBE/core/entities/Adaptor.h"

#include "ludo/entities/LudoAvatars.h"
#include "ludo/entities/LudoEntities.h"
#include "ludo/archetypes/LudoArchetypes.h"

namespace ludo {

class RotatedDrawableSimpleRotatedSpriteAdaptor : public zbe::Adaptor<SimpleRotatedSprite> {
public:
  RotatedDrawableSimpleRotatedSpriteAdaptor(const RotatedDrawableSimpleRotatedSpriteAdaptor&) = delete;
  void operator=(const RotatedDrawableSimpleRotatedSpriteAdaptor&) = delete;

  RotatedDrawableSimpleRotatedSpriteAdaptor(RotatedDrawable* archetype):archetype(archetype), s(nullptr){}

  ~RotatedDrawableSimpleRotatedSpriteAdaptor() {delete s;}

  SimpleRotatedSprite* getAvatar() {
    delete s;
    s = new SimpleRotatedSprite();
    s->x = archetype->getX();
    s->y = archetype->getY();
    s->w = archetype->getW();
    s->h = archetype->getH();
    s->graphics = archetype->getGraphics();
    s->angle = archetype->getAngle();
    s->angle = (s->angle < 0 ? 360.0 + s->angle : s->angle );
    return (s);
  };

private:
  RotatedDrawable* archetype;
  SimpleRotatedSprite* s;
};

/** \brief Adapts a Ludoball to a Collisionator.
 */
template <typename R>
class LudoBallCollisionatorAdaptor : public zbe::Adaptor<zbe::Collisionator<R> > {
public:
  LudoBallCollisionatorAdaptor(const LudoBallCollisionatorAdaptor&) = delete;
  void operator=(const LudoBallCollisionatorAdaptor&) = delete;

  LudoBallCollisionatorAdaptor(LudoBall<R>* ball): b(ball), c(nullptr) {}

  ~LudoBallCollisionatorAdaptor() {delete c;}

  zbe::Collisionator<R>* getAvatar() {
      delete c;
      std::shared_ptr<zbe::CollisionObject<R> > co = std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::ConstantMovingCircle<R>(zbe::Circle(b->getPosition(), b->getWidth()), b->getVelocity()));
      std::shared_ptr<zbe::ReactObject<R> > ro = std::make_shared<zbe::VoidReactObject<R> >();
//      zbe::Bouncer<2>* bouncer;
//      zbe::assignAvatar(b, &bouncer);
//      c = new zbe::CollisionatorCommon<GameReactor, zbe::AvatarEntity<zbe::Bouncer<2> > >(new TypeContainer<zbe::AvatarEntity<zbe::Bouncer<2> > >(b), co, ro, b->getActuatorsList() ,b->getCollisionablesList());
      c = new zbe::CollisionatorCommon<R, zbe::Bouncer<2> >(new zbe::AvatarEntityContainer<zbe::Bouncer<2> >(b), co, ro, b->getActuatorsList() ,b->getCollisionablesList());
      return (c);
    }

private:
	LudoBall<R>* b;
	zbe::Collisionator<R>* c;
};

} // namespace

#endif //ZBE_MAIN_LUDO_ENTITIES_LUDOADAPTORS
