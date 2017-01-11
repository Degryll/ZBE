/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseMovableMobileAdaptor.h
 * @since 2016-12-16
 * @date 2016-12-18
 * @author Degryll
 * @brief Implementation that adapts a position entity to a positionable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BASEPOSITIONABLEPOSITIONADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BASEPOSITIONABLEPOSITIONADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Positionable.h"
#include "ZBE/entities/adaptors/PositionableAdaptor.h"
#include "ZBE/entities/avatars/implementations/BasePositionable.h"
#include "ZBE/archetypes/Position.h"

namespace zbe {

/** \brief Implementation that adapts a mobile entity to a movable.
 */
template <unsigned s>
class BasePositionablePositionAdaptor : public PositionableAdaptor<Position<s>, s> {
  public:
    std::shared_ptr< Positionable<s> > getPositionable(Position<s>* entity) {return (std::make_shared<BasePositionable<s> >(entity));};
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BASEPOSITIONABLEPOSITIONADAPTOR_H_
