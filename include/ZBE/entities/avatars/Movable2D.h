/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movable2D.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief This define an avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_MOVABLE2D_H_
#define ZBE_ENTITIES_AVATARS_MOVABLE2D_H_

namespace zbe {

/** \brief This define an avatar that can be moved.
 */
class Movable2D {
  public:
    virtual void setX(double x) = 0;
    virtual void setY(double y) = 0;
    virtual void setPosition(double x, double y) = 0;
    virtual void setPosition(Point2D position) = 0;

    virtual void setVelocityX(double x) = 0;
    virtual void setVelocityY(double y) = 0;
    virtual void setVelocity(double x, double y) = 0;
    virtual void setVelocity(Vector2D velocity) = 0;

    virtual double getX() = 0;
    virtual double getY() = 0;
    virtual Point2D getPosition() = 0;
    virtual double getVelocityX() = 0;
    virtual double getVelocityY() = 0;
    virtual Vector2D getVelocity() = 0;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_MOVABLE2D_H_
