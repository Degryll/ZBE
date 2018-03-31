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

namespace zombienoid {

/** \brief This define an avatar that can be moved.
 */
class BoundedWrapperPositionable2D : virtual public zbe::Positionable<2> {
  public:
    BoundedWrapperPositionable2D(const BoundedWrapperPositionable2D&) = delete; //<! Avoid copy
    void operator=(const BoundedWrapperPositionable2D&) = delete; //<! Avoid copy

    /** \brief Virtual destructor.
     */
    virtual ~BoundedWrapperPositionable2D(){}

    /** \brief Builds this BasePositionable with a Position.
     */
    BoundedWrapperPositionable2D(std::shared_ptr<zbe::AvatarEntity<zbe::Positionable<2> > > positionable2d, double xMin, double yMin, double xMax, double yMax, double xOffset, double yOffset)
        : p2d(positionable2d),  xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax), xOff(xOffset), yOff(yOffset) {}

    /** \brief Sets the position for this Positionable.
     * \param List of values for the position..
     */
    void setPosition(std::initializer_list<double> l) { this->setPosition(zbe::Point2D(l));}

    /** \brief Sets the position for this Positionable.
     * \param The position.
     */
    void setPosition(zbe::Point2D position) {
      zbe::Positionable<2>* pable2;
      p2d->assignAvatar(&pable2);
      pable2->setPosition(zbe::Point2D({std::min(std::max(xMin, position.x + xOff), xMax), std::min(std::max(yMin, position.y + yOff), yMax)}));
    }

    /** \brief Retunrs the position of this Positionable.
     * \return The position.
     */
    zbe::Point<2>& getPosition() {
      zbe::Positionable<2>* pable2;
      p2d->assignAvatar(&pable2);
      return (pable2->getPosition());
    }

  private:
    std::shared_ptr<zbe::AvatarEntity<Positionable<2> > > p2d;
    double xMin;
    double yMin;
    double xMax;
    double yMax;
    double xOff;
    double yOff;
};

}  // namespace zombienoid

#endif  // ZOMBIENOID_ENTITIES_AVATARS_BOUNDEDWRAPPERPOSITIONABLE2D_H_
