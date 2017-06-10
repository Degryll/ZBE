/**
 * Copyright 2011 Batis Degryll Ludo
 * @file Element2D.h
 * @since 2017-06-04
 * @date 2017-06-04
 * @author Batis Degryll Ludo
 * @brief A simple game element in 2D.
 */

#ifndef ZBE_ENTITIES_ELEMENT2D_H
#define ZBE_ENTITIES_ELEMENT2D_H

#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/avatars/Collisioner.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/Entity.h"

#include "ZBE/archetypes/implementations/SimplePositionPO.h"
#include "ZBE/archetypes/implementations/SimpleState.h"
#include "ZBE/archetypes/implementations/SimpleTimeStamp.h"
#include "ZBE/archetypes/PositionPO.h"
#include "ZBE/archetypes/SimpleState.h"
#include "ZBE/archetypes/TimeStamp.h"
#include "ZBE/entities/avatars/Positionable.h"
#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/implementations/BaseStated.h"

namespace zbe {

template<typename R>
class Element2D: public zbe::Entity,
  							 public zbe::SimpleTimeStamp,
  							 public zbe::Drawable,
  							 public zbe::SimplePositionPO<2>,
  							 public zbe::SimpleState,
  							 public zbe::AvatarEntityFixed<zbe::Avatar>,
  							 public zbe::AvatarEntityAdapted<zbe::AnimatedSprite>,
  							 public zbe::AvatarEntityAdapted<zbe::Collisioner<R> >,
  							 public zbe::AvatarEntityFixed<zbe::Positionable<2> >,
  							 public zbe::AvatarEntityFixed<zbe::Stated> {
public:

  Element2D(Pont2D position, uint64_t actuatorsList, int64_t width, int64_t height, uint64_t graphics)
    : zbe::SimpleMobilePO<2>(position, actuatorList), w(width), h(height), g(graphics), ea(0) {
    zbe::AvatarEntityFixed<zbe::Avatar>::setAvatar(new zbe::BaseAvatar(this));
    zbe::AvatarEntityFixed<zbe::Positionable<2> >::setAvatar(new zbe::SimplePositionable<2>(this));
    zbe::AvatarEntityFixed<zbe::Stated>::setAvatar(new zbe::BaseStated(this));
  }

  int64_t getX() {return (PositionPO::getPosition()[0]);}
  int64_t getY() {return (PositionPO::getPosition()[1]);}
  int64_t getW() {return (w);}
  int64_t getH() {return (h);}
  uint64_t getGraphics() {return (g);}

private:

  int64_t w;
  int64_t h;
  uint64_t g;
  int64_t ea;
}

} // namespace zbe

#endif  // ZBE_ENTITIES_ELEMENT2D_H
