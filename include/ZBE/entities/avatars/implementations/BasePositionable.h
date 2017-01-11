/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Positionable.h
 * @since 2016-12-16
 * @date 2017-01-11
 * @author Batis Degryll Ludo
 * @brief This defines an avatar that can be posicioned.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEPOSITIONABLE_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEPOSITIONABLE_H_

#include "ZBE/entities/avatars/Positionable.h"
#include "ZBE/archetypes/Position.h"


namespace zbe {

/** \brief This define an avatar that can be moved.
 */
template <unsigned s>
class BasePositionable : public Positionable<s> {
  public:
    BasePositionable(const BasePositionable&) = delete;
    void operator=(const BasePositionable&) = delete;

    BasePositionable(Position<s> *position) : p(position) {}

    void setPosition(std::initializer_list<double> l) { p->setPosition(l);}
    void setPosition(Point<s> position) {p->setPosition(position);}

  Point<s>& getPosition() {return (p->getPosition());}
  private:
    Position<s> *p;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEPOSITIONABLE_H_
