/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleDrawableSimpleSpriteAdaptor.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESIMPLESPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESIMPLESPRITEADAPTOR_H_

#include <memory>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/entities/avatars/SimpleSprite.h"
#include "ZBE/core/entities/adaptors/SimpleSpriteAdaptor.h"
#include "ZBE/archetypes/Drawable.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a SimpleSprite.
 */
class SimpleDrawableSimpleSpriteAdaptor : public SimpleSpriteAdaptor<Drawable> {
  public:
    virtual std::shared_ptr<SimpleSprite> getSimpleSprite(Drawable* entity) {
      std::shared_ptr<SimpleSprite> s = std::make_shared<SimpleSprite>();

      s->x = entity->getX() >> zbe::PRECISION_DIGITS;
      s->y = entity->getY() >> zbe::PRECISION_DIGITS;
      s->w = entity->getW() >> zbe::PRECISION_DIGITS;
      s->h = entity->getH() >> zbe::PRECISION_DIGITS;
      s->graphics = entity->getGraphics();

      return (s);
    }
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESIMPLESPRITEADAPTOR_H_
