/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovable.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Degryll Ludo Batis
 * @brief This implements a base 1:1 avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEMOVABLE_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEMOVABLE_H_

#include <initializer_list>

#include "ZBE/core/tools/math/Vector.h"

#include "ZBE/entities/avatars/implementations/BasePositionable.h"
#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/archetypes/Mobile.h"

namespace zbe {

/** \brief This implements a base 1:1 avatar that can be moved.
 */
template <unsigned s>
class BaseMovable : virtual public Movable<s>, public BasePositionable<s> {
  public:
    BaseMovable(const BaseMovable&) = delete; //<! Avoid copy
    void operator=(const BaseMovable&) = delete; //<! Avoid copy

    /** \brief Builds this BaseMovable with a Mobile.
     */
    BaseMovable(Mobile<s>* mobile) : BasePositionable<s>(mobile), m(mobile) {}

    /** \brief Sets the velocity for this movable.
     * \param List of values for the velocity.
     */
    void setVelocity(std::initializer_list<double> l) {m->setVelocity(l);}

    /** \brief Sets the velocity for this movable.
     * \param The velocity.
     */
    void setVelocity(Vector<s> velocity)  {m->setVelocity(velocity);}

    /** \brief Returns actual velocity of this movable.
     * \return Actual velocity.
     */
    Vector<s>& getVelocity() {return (m->getVelocity());}

  private:
    Mobile<s>* m;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEMOVABLE_H_
