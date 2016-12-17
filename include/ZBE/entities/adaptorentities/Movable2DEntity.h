/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Movable2DEntity.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief Entity that can be seen as a movable 2D.
 */

#ifndef ZBE_ENTITIES_ADAPTORENTITIES_MOVABLE2DENTITY_H_
#define ZBE_ENTITIES_ADAPTORENTITIES_MOVABLE2DENTITY_H_

#include <memory>

#include "ZBE/entities/adaptors/Movable2DAdaptor.h"
#include "ZBE/entities/avatars/Movable2D.h"

namespace zbe {

/** \brief Entity that can be seen as a movable 2D.
 */
class Movable2DEntity {
  public:

    virtual std::shared_ptr<Movable2D> getMovable2D() = 0;

};

/** \brief Entity that can be seen as a movable 2D using an adaptor.
 */
template <typename T>
class Movable2DEntityAdapted : public Movable2D {
  public:
    Movable2DEntityAdapted(T* entity) : entity(entity) {}

    void setAdaptor(Movable2DAdaptor *adaptor) {a = adaptor;}

    std::shared_ptr<Movable2D> getMovable2D() {return (a->getMovable2D(entity));}

  private:
    T* entity;
    Movable2DAdaptor *a;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORENTITIES_MOVABLE2DENTITY_H_
