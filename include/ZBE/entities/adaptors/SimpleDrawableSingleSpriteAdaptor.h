/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleDrawableSingleSpriteAdaptor.h
 * @since 2017-03-22
 * @date 2017-05-10
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESINGLESPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESINGLESPRITEADAPTOR_H_

#include "ZBE/core/entities/avatars/SingleSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/Drawable.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a SingleSprite.
 */
class SimpleDrawableSingleSpriteAdaptor : public Adaptor<SingleSprite> {
public:
  SimpleDrawableSingleSpriteAdaptor(const SimpleDrawableSingleSpriteAdaptor&) = delete;
  void operator=(const SimpleDrawableSingleSpriteAdaptor&) = delete;

  SimpleDrawableSingleSpriteAdaptor(Drawable* entity): e(entity), s(nullptr) {}
  ~SimpleDrawableSingleSpriteAdaptor() {delete s;}
    SingleSprite* getAvatar() {
      delete s;
      s = new SingleSprite();

      s->x = e->getX();
      s->y = e->getY();
      s->w = e->getW();
      s->h = e->getH();
      s->graphics = e->getGraphics();

      return (s);
    }

private:
	Drawable* e;
	SingleSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_SIMPLEDRAWABLESINGLESPRITEADAPTOR_H_
