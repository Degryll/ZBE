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
#include "ZBE/archetypes/implementations/SimpleWideBouncingAPO.h"
#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/avatars/implementations/BaseBouncer.h"
#include "ZBE/reactobjects/VoidReactObject.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/implementations/SimpleCollisioner.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/tools/math/objects.h"

#include "ludo/archetypes/LudoArchetypes.h"
#include "ludo/entities/LudoAvatars.h"

namespace ludo {


/* Final entities */

template<typename R>
class LudoBall: public RotatedDrawable,
                public SetableGraphics,
                public zbe::SimpleWideBouncingAPO<2>,
                public zbe::AvatarEntityAdapted<SimpleRotatedSprite>,
                public zbe::AvatarEntityFixed<zbe::Bouncer<2> >,
                public zbe::AvatarEntityAdapted<zbe::Collisionator<R> > {
public:
  LudoBall(const LudoBall&) = delete;
  void operator=(const LudoBall&) = delete;

  LudoBall(double x, double y, double radius, double vx, double vy, uint64_t actuators, uint64_t collisionables, uint64_t graphics) :
      SimpleWideBouncingAPO({x, y}, {vx, vy}, radius, actuators, collisionables),
      g(graphics), r(radius), d(2*radius) {
      AvatarEntityFixed<zbe::Bouncer<2> >::setAvatar(new zbe::BaseBouncer<2>(this));
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
    zbe::AvatarEntityFixed<zbe::Collisioner<R> >(new zbe::SimpleCollisioner<R>(std::make_shared<zbe::StaticLimiterAABB2D<R> >(zbe::AABB2D({x, y}, {width, height} )),
         std::make_shared<zbe::VoidReactObject<R> >(),
         actuatorsList)) {}
};

} // namespace

#endif //ZBE_MAIN_LUDO_ENTITIES_LUDOENTITIES
