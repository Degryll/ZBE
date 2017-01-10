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

#include "ZBE/core/entities/avatars/SimpleSprite.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a SimpleSprite.
 */
class SimpleDrawableSimpleSpriteAdaptor : public DrawableAdaptor<Drawable> {
  public:
    virtual std::shared_ptr<Drawable> getDrawable(Drawable* entity) {
      SimpleSprite *s = new SimpleSprite;

      s->x = entity->getX();
      s->y = entity->getY();
      s->w = entity->getW();
      s->h = entity->getH();
      s->graphics = entity->getGraphics();
    }
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESIMPLESPRITEADAPTOR_H_
