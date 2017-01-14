/**
 * Copyright 2012 Batis Degryll Ludo
 * @file UniformLinearMotion.h
 * @since 2017-01-13
 * @date 2017-01-13
 * @author Degryll
 * @brief Implements an uniform linear motion behavior.
 */

#ifndef ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_
#define ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_

#include "zbe/core/behaviors/Behavior.h"
#include "zbe/archetypes/Mobile.h"
#include "ZBE/core/tools/math/math.h"
#include "ZBE/core/tools/math/Point.h"

namespace zbe {

/** \brief Define the minimal functions of every behavior.
 */
template<unsigned s>
class UniformLinearMotion : public Behavior< Mobile<s> > {
  public:

    /** \brief Default destructor.
     */
    virtual ~UniformLinearMotion() {}

    /** \brief Do the behavior work over the given entity
     */
    void apply(Mobile<s>* entity, uint64_t time) {
      Point<s>& p = entity->getPosition();
      p += entity->getVelocity() * (time * TIMETOVELOCITY);
    }
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_
