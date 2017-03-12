/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Bouncer.h
 * @since 2017-03-07
 * @date 2017-03-07
 * @author Batis Degryll Ludo
 * @brief This define an avatar of an entity that can bounce with multiple normals.
 */

#ifndef ZBE_ENTITIES_AVATARS_BOUNCER_H_
#define ZBE_ENTITIES_AVATARS_BOUNCER_H_

#include "ZBE/core/tools/math/Vector.h"

namespace zbe {

/** \brief This define an avatar of an entity that can bounce with multiple normals.
 */
template <unsigned s>
class Bouncer {
  public:
    virtual ~Bouncer() {}
  	virtual void addNormal(const Vector<s>& normal) = 0;
  	virtual Vector<s> getNormalSum() = 0;
  	virtual bool hasNormals() = 0;
  	virtual void clearNormals() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_BOUNCER_H_
