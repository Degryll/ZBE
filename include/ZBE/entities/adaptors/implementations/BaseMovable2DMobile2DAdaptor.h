/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovable2DMobile2DAdaptor.h
 * @since 2016-12-16
 * @date 2016-12-16
 * @author Degryll
 * @brief Implementation that adapts a mobile2D entity to a movable2D.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BASEMOVABLE2DMOBILE2DADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BASEMOVABLE2DMOBILE2DADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Movable2D.h"
#include "ZBE/entities/avatars/BaseMovable2D.h"
#include "ZBE/archetypes/Mobile2D.h"

namespace zbe {

/** \brief Template that adapts an entity to a drawable.
 */
class BaseMovable2DMobile2DAdaptor : public Movable2DAdaptor<Mobile2D> {
  public:
    std::shared_ptr<Movable2D> getMovable2D(Mobile2D* entity) {return (new BaseMovable2D(entity));};
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BASEMOVABLE2DMOBILE2DADAPTOR_H_
