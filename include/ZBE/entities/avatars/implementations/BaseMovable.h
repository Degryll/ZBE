/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovable.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll Ludo Batis
 * @brief This implements a base 1:1 avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEMOVABLE_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEMOVABLE_H_

#include "ZBE/entities/avatars/implementations/BasePositionable.h"
#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/archetypes/Mobile.h"

namespace zbe {

/** \brief This implements a base 1:1 avatar that can be moved.
 */
template <unsigned s>
class BaseMovable : virtual public Movable<s>, public BasePositionable<s> {
  public:
    BaseMovable(const BaseMovable&) = delete;
    void operator=(const BaseMovable&) = delete;

    BaseMovable(Mobile<s>* mobile) : BasePositionable<s>(mobile), m(mobile) {}

    void setPosition(std::initializer_list<double> l) {m->setPosition(l);}
    void setPosition(Point<s> position)   {m->setPosition(position);}

    void setVelocity(std::initializer_list<double> l) {m->setVelocity(l);}
    void setVelocity(Vector<s> velocity)  {m->setVelocity(velocity);}

    Point<s>& getPosition()  {return (m->getPosition());}
    Vector<s>& getVelocity() {return (m->getVelocity());}

  private:
    Mobile<s>* m;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEMOVABLE_H_
