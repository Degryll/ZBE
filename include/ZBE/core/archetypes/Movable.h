/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movible.h
 * @since 2015-05-04
 * @date 2015-05-04
 * @author Degryll
 * @brief Define a class that can be moved around the world.
 */

#ifndef CORE_ARCHETYPES_MOVIBLE_H_
#define CORE_ARCHETYPES_MOVIBLE_H_

#include "ZBE/core/archetypes/Positionable.h"
#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

/** \brief Define a class that can be moved around the world.
 */
template<unsigned s>
class Movable : public Positionable<s> {
  public:
    virtual ~Movable() = 0;

    void setVelocity(Vector<s> velocity);
    Vector<s> getVelocity() const;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_MOVIBLE_H_
