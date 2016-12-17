/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseDampingBounceableAdaptor.h
 * @since 2016-12-17
 * @date 2016-12-17
 * @author Batis
 * @brief Implementation that adapts a Damping entity to a Bounceable entity.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_BASEDAMPINGBOUNCEABLEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_BASEDAMPINGBOUNCEABLEADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/Bounceable.h"
#include "ZBE/entities/avatars/implementations/SimpleBounceable.h"
#include "ZBE/archetypes/Damping.h"

namespace zbe {

class BaseDampingBounceableAdaptor : public BounceableAdaptor<Damping> {
  public:
    std::shared_ptr<Bounceable> getBounceable(Damping* entity) {return (new SimpleBounceable(entity));};
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_BASEDAMPINGBOUNCEABLEADAPTOR_H_
