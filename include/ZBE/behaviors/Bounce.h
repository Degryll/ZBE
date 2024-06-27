/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Bounce.h
 * @since 2017-01-13
 * @date 2017-05-10
 * @author Degryll Ludo
 * @brief Implements a bounce behavior.
 */

#ifndef ZBE_BEHAVIORS_BOUNCE_H_
#define ZBE_BEHAVIORS_BOUNCE_H_

#include <memory>

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Implements a bounce behavior.
 */
template<unsigned s>
class Bounce : virtual public Behavior<bool, Vector<s>, Vector<s> > {
public:

  /** \brief Virtual destructor.
   */
  virtual ~Bounce() {}

  /** \brief Changes the entity velocity with the accumulated normals.
   */
  void apply(std::shared_ptr<MAvatar<bool, Vector<s>, Vector<s> > > avatar) override {
    auto vhasNormals = AvtUtil::get<3, bool>(avatar);
    if(vhasNormals->get()) {
      auto vNormals = AvtUtil::get<2, Vector<s> >(avatar);
      auto vVelocity = AvtUtil::get<1, Vector<s> >(avatar);
      vVelocity->set(vVelocity->get().reflect(vNormals->get()));
      vhasNormals->set(false);
    }
  }
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_BOUNCE_H_
