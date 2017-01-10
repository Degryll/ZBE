/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSpriteAdaptor.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll
 * @brief Template that adapts an entity to a simple sprite.
 */

#ifndef ZBE_CORE_ENTITIES_ADAPTORS_SIMPLESPRITEADAPTOR_H_
#define ZBE_CORE_ENTITIES_ADAPTORS_SIMPLESPRITEADAPTOR_H_

#include <memory>

#include "ZBE/core/entities/avatars/SimpleSprite.h"

namespace zbe {

/** \brief Template that adapts an entity to a simple sprite.
 */
template <typename T>
class SimpleSpriteAdaptor {
  public:
    virtual std::shared_ptr<SimpleSprite> getSimpleSprite(T* entity) = 0;
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_ADAPTORS_SIMPLESPRITEADAPTOR_H_
