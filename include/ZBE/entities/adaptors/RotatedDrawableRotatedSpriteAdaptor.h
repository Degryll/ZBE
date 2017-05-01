/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedDrawableRotatedSpriteAdaptor.h
 * @since 2017-03-22
 * @date 2017-03-22
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ROTATEDDRAWABLEROTATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ROTATEDDRAWABLEROTATEDSPRITEADAPTOR_H_

#include <memory>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/entities/avatars/RotatedSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/RotatedDrawable.h"

namespace zbe {

/** \brief Implementation that adapts an RotatedDrawable to a RotatedSprite.
 */
class RotatedDrawableRotatedSpriteAdaptor : public Adaptor<RotatedSprite> {
public:
  RotatedDrawableRotatedSpriteAdaptor(const RotatedDrawableRotatedSpriteAdaptor&) = delete;
  void operator=(const RotatedDrawableRotatedSpriteAdaptor&) = delete;

  RotatedDrawableRotatedSpriteAdaptor(RotatedDrawable* entity): e(entity), s(nullptr) {}
  ~RotatedDrawableRotatedSpriteAdaptor() {delete s;}
    RotatedSprite* getAvatar() {
      delete s;
      s = new RotatedSprite();

      s->x = e->getX();
      s->y = e->getY();
      s->w = e->getW();
      s->h = e->getH();
      s->graphics = e->getGraphics();
      s->degrees  = e->getDegrees();

      return (s);
    }

private:
	RotatedDrawable* e;
	RotatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ROTATEDDRAWABLEROTATEDSPRITEADAPTOR_H_
