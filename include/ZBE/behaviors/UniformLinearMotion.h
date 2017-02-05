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

#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/archetypes/Mobile.h"
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
    void apply(Mobile<s>* entity, int64_t time) {
      Point<s>& p = entity->getPosition();
      //printf("--- Punto antes de mover: %ld x %ld\n", p[0], p[1]);fflush(stdout);
      //printf("Tiempo: %ld \n", time);fflush(stdout);
      for(unsigned i = 0; i < s; i++) {
      	p[i] += (entity->getVelocity()[i] * time) >> PRECISION_DIGITS;
      }
      //printf("Punto despues de mover de mover: %ld x %ld\n", p[0], p[1]);fflush(stdout);
    }
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_UNIFORMLINEARMOTION_H_
