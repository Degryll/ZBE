/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovable2D.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief This implements a base 1:1 avatar that can be moved.
 */

#ifndef ZBE_ENTITIES_AVATARS_BASEMOVABLE2D_H_
#define ZBE_ENTITIES_AVATARS_BASEMOVABLE2D_H_

#include "ZBE/entities/avatars/Movable2D.h"
#include "ZBE/archetypes/Mobile2D.h"


namespace zbe {

/** \brief This implements a base 1:1 avatar that can be moved.
 */
class BaseMovable2D {
  public:
    BaseMovable2D(Mobile2D* mobile) : m(mobile) {}

    void setX(double x)                  {m->setX(x);}
    void setY(double y)                  {m->setY(y);}
    void setPosition(double x, double y) {m->setPosition(x, y);}
    void setPosition(Point2D position)   {m->setPosition(position);}

    void setVelocityX(double x)          {m->setVelocityX(x);}
    void setVelocityY(double y)          {m->setVelocityY(y);}
    void setVelocity(double x, double y) {m->setVelocity(x, y);}
    void setVelocity(Vector2D velocity)  {m->setVelocity(velocity);}

    double getX()          {return (m->getX());}
    double getY()          {return (m->getY());}
    Point2D getPosition()  {return (m->getPosition());}
    double getVelocityX()  {return (m->getVelocityX());}
    double getVelocityY()  {return (m->getVelocityY());}
    Vector2D getVelocity() {return (m->getVelocity());}

  private:
    Mobile2D* m;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_BASEMOVABLE2D_H_
