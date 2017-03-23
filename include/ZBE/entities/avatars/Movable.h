/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movable.h
 * @since 2016-12-16
 * @date 2017-01-17
 * @author Degryll Ludo
 * @brief This define an avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_MOVABLE_H_
#define ZBE_ENTITIES_AVATARS_MOVABLE_H_

#include "ZBE/entities/avatars/Positionable.h"

namespace zbe {

/** \brief This define an avatar that can be moved.
 */
template <unsigned s>
class Movable : public Positionable<s> {
  public:
    using Base = Positionable<s>;

    virtual void setVelocity(std::initializer_list<double> l) = 0;
    virtual void setVelocity(Vector<s> velocity) = 0;

    virtual Vector<s>& getVelocity() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_MOVABLE_H_
