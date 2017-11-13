/**
 * Copyright 2012 Batis Degryll Ludo
 * @file LudoEntities.h
 * @since 2017-02-25
 * @date 2017-02-25
 * @author Ludo
 * @brief Entities for ludo's proving grounds.
 */

#ifndef ZBE_MAIN_LUDO_ENTITIES_LUDOENTITIES
#define ZBE_MAIN_LUDO_ENTITIES_LUDOENTITIES

#include <cstdint>
#include <memory>

#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/State.h"
#include "ZBE/archetypes/TimeStamp.h"
#include "ZBE/archetypes/implementations/SimpleTimeStamp.h"
#include "ZBE/archetypes/implementations/SimpleState.h"
#include "ZBE/archetypes/implementations/SimpleWideBouncingAPO.h"
#include "ZBE/archetypes/implementations/SimpleMobile.h"
#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/implementations/BaseStated.h"
#include "ZBE/entities/avatars/implementations/BaseBouncer.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/SingleSprite.h"
#include "ZBE/core/entities/avatars/RotatedSprite.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/avatars/implementations/VoidCollisioner.h"
#include "ZBE/core/entities/avatars/implementations/VoidCollisionator.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/tools/math/objects.h"

#include "ludo/archetypes/LudoArchetypes.h"
#include "ludo/entities/LudoAvatars.h"

namespace ludo {

/****  ReactObjects ****/

class Destroyer {
public:
    using Base = void;
};


/**** Final entities ****/

template<typename R>
class LudoBall: public RotatedDrawable,
                public SetableGraphics,
                public zbe::Entity,
                public zbe::SimpleWideBouncingAPO<2>,
                public zbe::AvatarEntityFixed<zbe::Avatar>,
                public zbe::AvatarEntityAdapted<zbe::RotatedSprite>,
                public zbe::AvatarEntityFixed<zbe::Bouncer<2> >,
                public zbe::AvatarEntityAdapted<zbe::Collisionator<R> > {
public:
  LudoBall(const LudoBall&) = delete;
  void operator=(const LudoBall&) = delete;

  LudoBall(double x, double y, double radius, double vx, double vy, uint64_t actuators, uint64_t collisionables, uint64_t graphics) :
      SimpleWideBouncingAPO({x, y}, {vx, vy}, radius, actuators, collisionables),
      g(graphics), r(radius), d(2*radius) {
      zbe::Avatar* a;
      a = new zbe::BaseAvatar(this);
      zbe::AvatarEntityFixed<zbe::Avatar>::setAvatar(a);
      zbe::AvatarEntityFixed<zbe::Bouncer<2> >::setAvatar(new zbe::BaseBouncer<2>(this));
  }

  int64_t getX() {return ((int64_t)SimpleWideBouncingAPO::getPosition()[0]-r);}
  int64_t getY() {return ((int64_t)SimpleWideBouncingAPO::getPosition()[1]-r);}
  int64_t getW() {return ((int64_t)d);}
  int64_t getH() {return ((int64_t)d);}
  double  getAngle() {return getVelocity().getDegrees();}
  uint64_t getGraphics() {return (g);}
  void setGraphics(unsigned graphics) {g = graphics;}

private:
  uint64_t g;    //!< Image index
  double r;
  double d;
};

template<typename R>
class LudoBoard : public zbe::AvatarEntityFixed<zbe::Collisioner<R> > {
public:
  LudoBoard(double x, double y, double width, double height, uint64_t actuatorsList) :
    zbe::AvatarEntityFixed<zbe::Collisioner<R> >(new zbe::VoidCollisioner<R>(std::make_shared<zbe::StaticLimiterAABB2D<R> >(zbe::AABB2D({x, y}, {width, height} )),
         std::make_shared<zbe::ReactObjectCommon<R> >(),
         actuatorsList)) {}
};


class BallParticle :    virtual public RotatedDrawable,
                        public zbe::SimpleState,
                        public zbe::AvatarEntityFixed<zbe::Stated>,
                        public zbe::AvatarEntityAdapted<zbe::RotatedSprite> {
public:
  BallParticle(double x, double y, double radius, uint64_t graphics, double angle):
       SimpleState(), g(graphics),
       x(x-radius),y(y-radius),
       d(2*radius), a(angle) {
    //zbe::AvatarEntityFixed<Stated>::setAvatar(&s);
  };

  int64_t getX() {return ((int64_t)x);}
  int64_t getY() {return ((int64_t)y);}
  int64_t getW() {return ((int64_t)d);}
  int64_t getH() {return ((int64_t)d);}
  double  getAngle() {return a;}
  uint64_t getGraphics() {return (g);}

private:
  uint64_t g;    //!< Image index
  double x, y;
  double d, a;
};

class GraphicElement :    virtual public RotatedDrawable,
                        public zbe::SimpleState,
                        public zbe::SimpleTimeStamp {
public:
  GraphicElement(double x, double y, double w, double h, int64_t state, uint64_t graphics, double angle, int64_t timeStamp):
       SimpleState(state), SimpleTimeStamp(timeStamp),
       g(graphics), x(x), y(y),
       w(w), h(h), a(angle) {
    //zbe::AvatarEntityFixed<Stated>::setAvatar(&s);
  };

  int64_t getX() {return ((int64_t)x);}
  int64_t getY() {return ((int64_t)y);}
  int64_t getW() {return ((int64_t)w);}
  int64_t getH() {return ((int64_t)h);}
  double  getAngle() {return a;}
  uint64_t getGraphics() {return (g);}

private:
  uint64_t g;    //!< Image index
  double x, y;
  double w, h;
  double a;
};


template<typename R>
class LudoCircleArea :  public zbe::AvatarEntityFixed<zbe::Collisionator<R> > {
public:
  LudoCircleArea(double x, double y, double radius, uint64_t actuatorsList, uint64_t collisionablesList, std::shared_ptr<zbe::ReactObject<R> > ro):
        zbe::AvatarEntityFixed<zbe::Collisionator<R> >(
          new zbe::VoidCollisionator<R>(
            std::make_shared<zbe::ConstantMovingCircle<R> >(zbe::ConstantMovingCircle<R>(zbe::Circle({x, y}, radius), {0, 0})),
            ro,
            actuatorsList, collisionablesList)){
  };
};


} // namespace

#endif //ZBE_MAIN_LUDO_ENTITIES_LUDOENTITIES
