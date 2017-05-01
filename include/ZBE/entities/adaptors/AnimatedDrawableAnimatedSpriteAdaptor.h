/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedDrawableAnimatedSpriteAdaptor.h
 * @since 2017-03-22
 * @date 2017-03-22
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ANIMATEDDRAWABLEANIMATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ANIMATEDDRAWABLEANIMATEDSPRITEADAPTOR_H_

#include <memory>

#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/AnimatedDrawable.h"

namespace zbe {

/** \brief Implementation that adapts an AnimatedDrawable to a AnimatedSprite.
 */
class AnimatedDrawableAnimatedSpriteAdaptor : public Adaptor<AnimatedSprite> {
public:
  AnimatedDrawableAnimatedSpriteAdaptor(const AnimatedDrawableAnimatedSpriteAdaptor&) = delete;
  void operator=(const AnimatedDrawableAnimatedSpriteAdaptor&) = delete;

  AnimatedDrawableAnimatedSpriteAdaptor(AnimatedDrawable* entity): e(entity), s(nullptr) {}
  ~AnimatedDrawableAnimatedSpriteAdaptor() {delete s;}
    AnimatedSprite* getAvatar() {
      delete s;
      s = new AnimatedSprite();

      s->x = e->getX();
      s->y = e->getY();
      s->w = e->getW();
      s->h = e->getH();
      s->graphics = e->getGraphics();
      s->degrees  = e->getDegrees();
      s->state    = e->getState();
      s->nstates  = e->getNumStates();
      s->frame    = e->getFrame();
      s->nframes  = e->getNumFrames(uint64_t state);
      s->width    = e->getW(uint64_t state);
      s->height   = e->getH(uint64_t state);

      return (s);
    }

private:
	AnimatedDrawable* e;
	AnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ANIMATEDDRAWABLEANIMATEDSPRITEADAPTOR_H_
