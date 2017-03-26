/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleDrawableSimpleSpriteAdaptor.h
 * @since 2017-03-22
 * @date 2017-03-22
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESIMPLESPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESIMPLESPRITEADAPTOR_H_

#include <memory>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/entities/avatars/SimpleSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/Drawable.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a SimpleSprite.
 */
class SimpleDrawableSimpleSpriteAdaptor : public Adaptor<SimpleSprite> {
public:
  SimpleDrawableSimpleSpriteAdaptor(const SimpleDrawableSimpleSpriteAdaptor&) = delete;
  void operator=(const SimpleDrawableSimpleSpriteAdaptor&) = delete;

  SimpleDrawableSimpleSpriteAdaptor(Drawable* entity): e(entity), s(nullptr) {}
  ~SimpleDrawableSimpleSpriteAdaptor() {delete s;}
    SimpleSprite* getAvatar() {
      delete s;
      s = new SimpleSprite();

      s->x = e->getX();
      s->y = e->getY();
      s->w = e->getW();
      s->h = e->getH();
      s->graphics = e->getGraphics();

      return (s);
    }

private:
	Drawable* e;
	SimpleSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESIMPLESPRITEADAPTOR_H_
