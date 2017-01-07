/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movable.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief This define an avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_MOVABLE_H_
#define ZBE_ENTITIES_AVATARS_MOVABLE_H_

#include "ZBE/core/entities/avatars/Collisioner.h"

namespace zbe {

/** \brief This define an avatar that can be moved.
 */
template <typename R, unsigned s>
class Movable : public CollisionerCommon<Movable<R, s>, R> {
  public:
    Movable(CollisionObject<R>* object, std::forward_list<Actuator<Movable, R> > * actuators) : CollisionerCommon<Movable<R, s>, R>(this, object) {}

    virtual void setPosition(std::initializer_list<double> l) = 0;
    virtual void setPosition(Point<s> position) = 0;

    virtual void setVelocity(std::initializer_list<double> l) = 0;
    virtual void setVelocity(Vector<s> velocity) = 0;

    virtual Point<s>& getPosition() = 0;
    virtual Vector<s>& getVelocity() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_MOVABLE_H_
