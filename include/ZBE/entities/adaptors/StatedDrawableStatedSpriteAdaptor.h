/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedDrawableStatedSpriteAdaptor.h
 * @since 2017-03-22
 * @date 2017-03-22
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_STATEDDRAWABLESTATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_STATEDDRAWABLESTATEDSPRITEADAPTOR_H_

#include <memory>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/entities/avatars/StatedSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/StatedDrawable.h"

namespace zbe {

/** \brief Implementation that adapts an StatedDrawable to a StatedSprite.
 */
class StatedDrawableStatedSpriteAdaptor : public Adaptor<StatedSprite> {
public:
  StatedDrawableStatedSpriteAdaptor(const StatedDrawableStatedSpriteAdaptor&) = delete;
  void operator=(const StatedDrawableStatedSpriteAdaptor&) = delete;

  StatedDrawableStatedSpriteAdaptor(StatedDrawable* entity): e(entity), s(nullptr) {}
  ~StatedDrawableStatedSpriteAdaptor() {delete s;}
    StatedSprite* getAvatar() {
      delete s;
      s = new StatedSprite();

      s->x = e->getX();
      s->y = e->getY();
      s->w = e->getW();
      s->h = e->getH();
      s->graphics = e->getGraphics();
      s->degrees  = e->getDegrees();
      s->state    = e->getState();
      s->nstates  = e->getNumStates();

      return (s);
    }

private:
	StatedDrawable* e;
	StatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_STATEDDRAWABLESTATEDSPRITEADAPTOR_H_
