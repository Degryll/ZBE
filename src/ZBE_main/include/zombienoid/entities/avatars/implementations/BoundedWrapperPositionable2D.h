/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BoundedWrapperPositionable2D.h
 * @since 2017-10-17
 * @date 2017-10-17
 * @author Batis Degryll Ludo
 * @brief This defines an avatar that can be positioned but keep itse
 */

#ifndef ZOMBIENOID_ENTITIES_AVATARS_BOUNDEDWRAPPERPOSITIONABLE2D_H_
#define ZOMBIENOID_ENTITIES_AVATARS_BOUNDEDWRAPPERPOSITIONABLE2D_H_

#include "ZBE/core/entities/AvatarEntity.h"

#include "ZBE/entities/avatars/Positionable.h"

namespace zbe {

/** \brief This define an avatar that can be moved.
 */
class BoundedWrapperPositionable2D : virtual public Positionable<2> {
  public:
    BoundedWrapperPositionable2D(const BoundedWrapperPositionable2D&) = delete; //<! Avoid copy
    void operator=(const BoundedWrapperPositionable2D&) = delete; //<! Avoid copy

    /** \brief Virtual destructor.
     */
    virtual ~BoundedWrapperPositionable2D(){}

    /** \brief Builds this BasePositionable with a Position.
     */
    BoundedWrapperPositionable2D(std::shared_ptr<zbe::AvatarEntity<Positionable<2> > > positionable2d, double xMin, double yMin, double xMax, double yMax)
        : p2d(positionable2d),  x0(xMin), y0(yMin), x1(xMax), y1(yMax) {}

    /** \brief Sets the position for this Positionable.
     * \param List of values for the position..
     */
    void setPosition(std::initializer_list<double> l) { this->setPosition(Point2D(l);}

    /** \brief Sets the position for this Positionable.
     * \param The position.
     */
    void setPosition(Point2D position) {
      p2d->setPosition(Point2D(std::min(std::max(x0,position.x), x1),std::min(std::max(y0,position.y), y1)));
    }

    /** \brief Retunrs the position of this Positionable.
     * \return The position.
     */
    Point<s>& getPosition() {return (p2d->getPosition());}

  private:
    std::shared_ptr<zbe::AvatarEntity<Positionable<2> > > p2d;
    double x0;
    double y0;
    double x1;
    double y1;
};

}  // namespace zbe

#endif  // ZOMBIENOID_ENTITIES_AVATARS_BOUNDEDWRAPPERPOSITIONABLE2D_H_
