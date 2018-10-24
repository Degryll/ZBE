/**
 * Copyright 2011 Batis Degryll Ludo
 * @file ActiveElement2D.h
 * @since 2017-06-18
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief A simple active game element in 2D.
 */

#ifndef ZBE_ENTITIES_ACTIVEELEMENT2D_H
#define ZBE_ENTITIES_ACTIVEELEMENT2D_H

#include <cstdint>
#include <memory>

#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
#include "ZBE/core/entities/avatars/Interactionator.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"
#include "ZBE/core/entities/Entity.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/math/Point.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/archetypes/implementations/SimpleBouncingAPO.h"
#include "ZBE/archetypes/implementations/SimpleState.h"
#include "ZBE/archetypes/implementations/SimpleTimeStamp.h"
#include "ZBE/archetypes/implementations/SimpleArea.h"
#include "ZBE/archetypes/Drawable.h"
#include "ZBE/archetypes/Area.h"
#include "ZBE/archetypes/BouncingAPO.h"
#include "ZBE/archetypes/State.h"
#include "ZBE/archetypes/TimeStamp.h"
#include "ZBE/archetypes/Countable.h"
#include "ZBE/entities/avatars/Bouncer.h"
#include "ZBE/entities/avatars/Stated.h"
#include "ZBE/entities/avatars/implementations/BaseStated.h"
#include "ZBE/entities/avatars/implementations/BaseBouncer.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief A simple active game element in 2D..
 */
template<typename R>
class ZBEAPI ActiveElement2D: public Entity,
                       public SimpleTimeStamp,
                       public Drawable,
                       public SimpleBouncingAPO<2>,
                       public SimpleArea,
                       public SimpleState,
                       public AvatarEntityFixed<Avatar>,
                       public AvatarEntityAdapted<AnimatedSprite>,
                       public AvatarEntityAdapted<Interactionator<R> >,
                       public AvatarEntityFixed<Bouncer<2> >,
                       public AvatarEntityFixed<Stated> {
public:

  /** \brief Constructs a ActiveElement2D form its raw data
   *  \param position Entity position
   *  \param velocity Entity velocity
   *  \param actuatorsList actuators list id
   *  \param collisionersList collisioners list id
   *  \param width Entity width
   *  \param height Entity height
   *  \param graphics graphics id
   */
  ActiveElement2D(Point2D position, Vector2D velocity, uint64_t actuatorsList, uint64_t collisionersList, int64_t width, int64_t height, uint64_t graphics)
    : SimpleTimeStamp(0),
    SimpleBouncingAPO<2>(position, velocity, actuatorsList, collisionersList), SimpleArea(width, height), g(graphics) {
    AvatarEntityFixed<Avatar>::setAvatar(new BaseAvatar(this));
    AvatarEntityFixed<Bouncer<2> >::setAvatar(new BaseBouncer<2>(this));
    AvatarEntityFixed<Stated>::setAvatar(new BaseStated(this));
  }

  /** \brief Getter for the x coord.
   *  \return x coord
   */
  int64_t getX() {return (SimpleBouncingAPO<2>::getPosition()[0]);}

  /** \brief Getter for the y coord.
   *  \return y coord
   */
  int64_t getY() {return (SimpleBouncingAPO<2>::getPosition()[1]);}

  /** \brief Getter for the width
   *  \return width
   */
  int64_t getW() {return (SimpleArea::getWidth());}

  /** \brief Getter for the height
   *  \return height
   */
  int64_t getH() {return (SimpleArea::getHeight());}

  /** \brief Getter for the graphics id.
   *  \return the graphics id
   */
  uint64_t getGraphics() {return (g);}

private:

  uint64_t g;
};

template<typename R>
class ZBEAPI CActiveElement2D : public Countable<int64_t>, public ActiveElement2D<R> {
public:
  CActiveElement2D(std::shared_ptr<Value<int64_t> > ninstances, Point2D position, Vector2D velocity, uint64_t actuatorsList, uint64_t collisionersList, int64_t width, int64_t height, uint64_t graphics)
    : Countable<int64_t>(ninstances), ActiveElement2D<R>(position, velocity, actuatorsList, collisionersList, width, height,  graphics){}
};

} // namespace zbe

#endif  // ZBE_ENTITIES_ACTIVEELEMENT2D_H
