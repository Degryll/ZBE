/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Positionable.h
 * @since 2016-12-16
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief This defines an avatar that can be posicioned.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEPOSITIONABLE_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEPOSITIONABLE_H_

#include <initializer_list>

#include "ZBE/core/tools/math/Point.h"

#include "ZBE/entities/avatars/Positionable.h"
#include "ZBE/archetypes/Position.h"


namespace zbe {

/** \brief This define an avatar that can be moved.
 */
template <unsigned s>
class BasePositionable : virtual public Positionable<s> {
  public:
    BasePositionable(const BasePositionable&) = delete; //<! Avoid copy
    void operator=(const BasePositionable&) = delete; //<! Avoid copy

    /** \brief Virtual destructor.
     */
    virtual ~BasePositionable(){}

    /** \brief Builds this BasePositionable with a Position.
     */
    BasePositionable(Position<s> *position) : p(position) {}

    /** \brief Sets the position for this Positionable.
     * \param List of values for the position..
     */
    void setPosition(std::initializer_list<double> l) { p->setPosition(l);}

    /** \brief Sets the position for this Positionable.
     * \param The position.
     */
    void setPosition(Point<s> position) {p->setPosition(position);}

    /** \brief Retunrs the position of this Positionable.
     * \return The position.
     */
    Point<s>& getPosition() {return (p->getPosition());}

  private:
    Position<s> *p;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASEPOSITIONABLE_H_
