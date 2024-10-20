///**
// * Copyright 2011 Batis Degryll Ludo
// * @file Element2D.h
// * @since 2017-06-04
// * @date 2018-02-25
// * @author Batis Degryll Ludo
// * @brief A simple game element in 2D.
// */
//
//#ifndef ZBE_ENTITIES_ELEMENT2D_H
//#define ZBE_ENTITIES_ELEMENT2D_H
//
//#include <cstdint>
//#include <memory>
//
//#include "ZBE/core/entities/avatars/implementations/BaseAvatar.h"
//#include "ZBE/core/entities/avatars/Interactioner.h"
//#include "ZBE/core/entities/avatars/Avatar.h"
//#include "ZBE/core/entities/avatars/AnimatedSprite.h"
//#include "ZBE/core/entities/AvatarEntity.h"
//#include "ZBE/core/entities/Entity.h"
//#include "ZBE/core/tools/shared/Value.h"
//#include "ZBE/core/tools/math/Point.h"
//#include "ZBE/core/tools/math/Vector.h"
//
//#include "ZBE/archetypes/implementations/SimplePositionPO.h"
//#include "ZBE/archetypes/implementations/SimpleState.h"
//#include "ZBE/archetypes/implementations/SimpleTimeStamp.h"
//#include "ZBE/archetypes/implementations/SimpleArea.h"
//#include "ZBE/archetypes/Area.h"
//#include "ZBE/archetypes/PositionPO.h"
//#include "ZBE/archetypes/State.h"
//#include "ZBE/archetypes/TimeStamp.h"
//#include "ZBE/archetypes/Countable.h"
//#include "ZBE/archetypes/Drawable.h"
//#include "ZBE/entities/avatars/Positionable.h"
//#include "ZBE/entities/avatars/Stated.h"
//#include "ZBE/entities/avatars/implementations/BaseStated.h"
//#include "ZBE/entities/avatars/implementations/BasePositionable.h"
//
//#include "ZBE/core/system/system.h"
//
//namespace zbe {
//
///** \brief A simple game element in 2D.
// */
//template<typename R>
//class Element2D: public Entity,
//                 public SimpleTimeStamp,
//                 public Drawable,
//                 public SimplePositionPO<2>,
//                 public SimpleArea,
//                 public SimpleState,
//                 public AvatarEntityFixed<Avatar>,
//                 public AvatarEntityAdapted<AnimatedSprite>,
//                 public AvatarEntityAdapted<Interactioner<R> >,
//                 public AvatarEntityFixed<Positionable<2> >,
//                 public AvatarEntityFixed<Stated> {
//public:
//
//
//
//  /** \brief Constructs a ActiveElement2D form its raw data
//   *  \param position Entity position
//   *  \param actuatorsList actuators list id
//   *  \param width Entity width
//   *  \param height Entity height
//   *  \param graphics graphics id
//   */
//  Element2D(Point2D position, uint64_t actuatorsList, int64_t width, int64_t height, uint64_t graphics)
//    : SimpleTimeStamp(0),
//    SimplePositionPO<2>(position, actuatorsList), SimpleArea(width, height), g(graphics), ea(0) {
//    AvatarEntityFixed<Avatar>::setAvatar(new BaseAvatar(this));
//    AvatarEntityFixed<Positionable<2> >::setAvatar(new BasePositionable<2>(this));
//    AvatarEntityFixed<Stated>::setAvatar(new BaseStated(this));
//  }
//
//
//  /** \brief Getter for the x coord.
//  *  \return x coord
//  */
//  int64_t getX() {return (SimplePositionPO::getPosition()[0]);}
//
//  /** \brief Getter for the y coord.
//   *  \return y coord
//   */
//  int64_t getY() {return (SimplePositionPO::getPosition()[1]);}
//
//  /** \brief Getter for the width
//   *  \return width
//   */
//  int64_t getW() {return (SimpleArea::getWidth());}
//
//  /** \brief Getter for the height
//   *  \return height
//   */
//  int64_t getH() {return (SimpleArea::getHeight());}
//
//  /** \brief Getter for the graphics id.
//   *  \return the graphics id
//   */
//  uint64_t getGraphics() {return (g);}
//
//private:
//  uint64_t g;
//  int64_t ea;
//};
//
//template<typename R>
//class CElement2D : public Countable<int64_t>, public Element2D<R> {
//public:
//  CElement2D (std::shared_ptr<Value<int64_t> > ninstances, Point2D position, uint64_t actuatorsList, int64_t width, int64_t height, uint64_t graphics)
//  : Countable<int64_t>(ninstances), Element2D<R>(position, actuatorsList, width, height, graphics) {}
//};
//
//} // namespace zbe
//
//#endif  // ZBE_ENTITIES_ELEMENT2D_H
