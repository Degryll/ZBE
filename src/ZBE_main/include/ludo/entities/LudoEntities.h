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

#include "ZBE/core/tools/math/objects.h"
#include "ZBE/core/entities/adaptorentities/CollisionerEntity.h"
#include "ZBE/core/entities/avatars/implementations/SimpleCollisioner.h"
#include "ZBE/core/entities/adaptorentities/SimpleSpriteEntity.h"
#include "ZBE/entities/adaptorentities/MovableCollisionatorEntity.h"
#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/implementations/SimpleWideMobileAPO.h"
#include "ZBE/reactobjects/VoidReactObject.h"

#include "ludo/entities/LudoAvatars.h"
#include "ludo/entities/LudoAdaptors.h"

namespace ludo {

/* Abstract entities */

/** \brief Entity that can be seen as a simple sprite.
 */
class SimpleRotatedSpriteEntity {
  public:
    virtual ~SimpleRotatedSpriteEntity() {};
    virtual std::shared_ptr<SimpleRotatedSprite> getSimpleRotatedSprite() = 0;
};

/** \brief Entity that can be seen as a simple sprite using an adaptor.
 */
template <typename T>
class SimpleRotatedSpriteEntityAdapted : public SimpleRotatedSpriteEntity {
  public:
    SimpleRotatedSpriteEntityAdapted(const SimpleRotatedSpriteEntityAdapted&) = delete;
    void operator=(const SimpleRotatedSpriteEntityAdapted&) = delete;

    SimpleRotatedSpriteEntityAdapted(T* entity) : entity(entity), a(nullptr) {}

    virtual ~SimpleRotatedSpriteEntityAdapted(){delete a;};

    void setSimpleRotatedSpriteAdaptor(SimpleRotatedSpriteAdaptor<T> *adaptor) {a = adaptor;}

    std::shared_ptr<SimpleRotatedSprite> getSimpleRotatedSprite() {return (a->getSimpleRotatedSprite(entity));}

  private:
    T* entity;
    SimpleRotatedSpriteAdaptor<T> *a;
};

/* Final entities */

template<typename R>
class LudoBall: public ludo::RotatedDrawable,
              public zbe::SimpleWideMobileAPO<2>,
              public SimpleRotatedSpriteEntityAdapted<ludo::RotatedDrawable>,
              public zbe::MovableCollisionatorEntityAdapted<R, zbe::SimpleWideMobileAPO<2>, 2> {
public:
        LudoBall(const LudoBall&) = delete;
  void operator=(const LudoBall&) = delete;

  LudoBall(double x, double y, double radius, double vx, double vy, double actuators, double collisionables, int graphics) :
              SimpleWideMobileAPO({x, y}, {vx, vy}, radius, actuators, collisionables),
              SimpleRotatedSpriteEntityAdapted(this),
              zbe::MovableCollisionatorEntityAdapted<R, zbe::SimpleWideMobileAPO<2>, 2>(this),
              g(graphics), r(radius), d(2*radius) {}

  ~LudoBall() {}

  int64_t getX()        {return (SimpleWideMobileAPO::getPosition()[0]-r);}
  int64_t getY()        {return (SimpleWideMobileAPO::getPosition()[1]-r);}
  int64_t getW()        {return (d);}
  int64_t getH()        {return (d);}
  double  getAngle()    {return getVelocity().getDegrees();}
  uint64_t getGraphics() {return (g);}

private:
  int g;    //!< Image index
  double r;
  double d;
};

template<typename R>
class LudoBoard : public zbe::CollisionerEntity<R> {
public:
  LudoBoard(double x1, double y1, double x2, double y2, uint64_t actuatorsList)
    : c(new zbe::SimpleCollisioner<R>(std::make_shared<zbe::StaticLimiterAABB2D<R> >(zbe::AABB2D(zbe::AABB2D({x1, y1}, {x2, y2} ))),
         std::make_shared<zbe::VoidReactObject<R> >(),
         actuatorsList)) {}

  std::shared_ptr<zbe::Collisioner<R> > getCollisioner() {return (c);}

private:
  std::shared_ptr<zbe::Collisioner<R> > c;
};

} // namespace

#endif //ZBE_MAIN_LUDO_ENTITIES_LUDOENTITIES
