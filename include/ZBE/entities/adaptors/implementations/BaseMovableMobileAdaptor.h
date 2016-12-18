/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovableMobileAdaptor.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Implementation that adapts a mobile entity to a movable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BASEMOVABLEMOBILEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BASEMOVABLEMOBILEADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Movable.h"
#include "ZBE/entities/avatars/BaseMovable.h"
#include "ZBE/archetypes/Mobile.h"

namespace zbe {

/** \brief Implementation that adapts a mobile entity to a movable.
 */
template <unsigned s>
class BaseMovableMobileAdaptor : public MovableAdaptor<Mobile<s>, s> {
  public:
    std::shared_ptr< Movable<s> > getMovable(Mobile<s>* entity) {return (new BaseMovable<s>(entity));};
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BASEMOVABLEMOBILEADAPTOR_H_
