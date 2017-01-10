/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSpriteEntity.h
 * @since 2016-11-23
 * @date 2016-11-23
 * @author Degryll
 * @brief Entity that can be seen as a simple sprite.
 */

#ifndef ZBE_CORE_ENTITIES_ADAPTORENTITIES_SIMPLESPRITEENTITY_H_
#define ZBE_CORE_ENTITIES_ADAPTORENTITIES_SIMPLESPRITEENTITY_H_

#include "ZBE/core/entities/adaptors/SimpleSpriteAdaptor.h"
#include "ZBE/core/entities/avatars/SimpleSprite.h"

namespace zbe {

/** \brief Entity that can be seen as a simple sprite.
 */
class SimpleSpriteEntity {
  public:

    virtual std::shared_ptr<SimpleSprite> getSimpleSprite() = 0;

};

/** \brief Entity that can be seen as a simple sprite using an adaptor.
 */
template <typename T>
class SimpleSpriteEntityEntityAdapted : public SimpleSprite {
  public:
    SimpleSpriteEntityEntityAdapted(T* entity) : entity(entity) {}

    virtual ~SimpleSpriteEntityEntityAdapted(){delete a;};

    void setAdaptor(SimpleSpriteAdaptor *adaptor) {a = adaptor;}

    std::shared_ptr<SimpleSprite> getSimpleSprite() {return (a->getSimpleSprite(entity));}

  private:
    T* entity;
    SimpleSpriteAdaptor *a;
};

}  // namespace zbe

#endif  // ZBE_CORE_ENTITIES_ADAPTORENTITIES_SIMPLESPRITEENTITY_H_
