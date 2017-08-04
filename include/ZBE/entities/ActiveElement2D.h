/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ActiveElement2D.h
 * @since 2017-06-18
 * @date 2017-06-18
 * @author Batis Degryll Ludo
 * @brief A simple active game element in 2D.
 */

#ifndef ZBE_ENTITIES_ACTIVEELEMENT2D_H
#define ZBE_ENTITIES_ACTIVEELEMENT2D_H

#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/avatars/Collisionator.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/Entity.h"

#include "ZBE/core/tools/shared/Value.h"

#include "ZBE/archetypes/implementations/SimpleWideBouncingAPO.h"
#include "ZBE/archetypes/implementations/SimpleState.h"
#include "ZBE/archetypes/implementations/SimpleTimeStamp.h"
#include "ZBE/archetypes/WideBouncingAPO.h"
#include "ZBE/archetypes/State.h"
#include "ZBE/archetypes/TimeStamp.h"
#include "ZBE/archetypes/Countable.h"

#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/implementations/BaseStated.h"
#include "ZBE/entities/avatars/implementations/BaseBouncer.h"

namespace zbe {

template<typename R>
class ActiveElement2D: public Entity,
                       public SimpleTimeStamp,
                       public Drawable,
                       public SimpleWideBouncingAPO<2>,
                       public SimpleState,
                       public AvatarEntityFixed<Avatar>,
                       public AvatarEntityAdapted<AnimatedSprite>,
                       public AvatarEntityAdapted<Collisionator<R> >,
                       public AvatarEntityFixed<Bouncer<2> >,
                       public AvatarEntityFixed<Stated> {
public:

  //using Avatars = std::tuple<Avatar, Bouncer<2>, Stated>;

  ActiveElement2D(Point2D position, Vector2D velocity, uint64_t actuatorsList, uint64_t collisionersList, int64_t width, int64_t height, uint64_t graphics)
    : SimpleTimeStamp(0),
    SimpleWideBouncingAPO<2>(position, velocity, width, actuatorsList, collisionersList), w(width), h(height), g(graphics) {
    AvatarEntityFixed<Avatar>::setAvatar(new BaseAvatar(this));
    AvatarEntityFixed<Bouncer<2> >::setAvatar(new BaseBouncer<2>(this));
    AvatarEntityFixed<Stated>::setAvatar(new BaseStated(this));
  }

  int64_t getX() {return (SimpleWideBouncingAPO<2>::getPosition()[0]);}
  int64_t getY() {return (SimpleWideBouncingAPO<2>::getPosition()[1]);}
  int64_t getW() {return (w);}
  int64_t getH() {return (h);}
  uint64_t getGraphics() {return (g);}

private:

  int64_t w;
  int64_t h;
  uint64_t g;
};

template<typename R>
class CActiveElement2D : public Countable<int64_t>, public ActiveElement2D<R> {
public:
  CActiveElement2D(std::shared_ptr<Value<int64_t> > ninstances, Point2D position, Vector2D velocity, uint64_t actuatorsList, uint64_t collisionersList, int64_t width, int64_t height, uint64_t graphics)
    : Countable<int64_t>(ninstances), ActiveElement2D<R>(position, velocity, actuatorsList, collisionersList, width, height,  graphics){}
};

} // namespace zbe

#endif  // ZBE_ENTITIES_ACTIVEELEMENT2D_H
