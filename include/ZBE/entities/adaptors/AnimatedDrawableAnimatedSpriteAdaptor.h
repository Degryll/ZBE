/**
 * Copyright 2012 Batis Degryll Ludo
 * @file AnimatedDrawableAnimatedSpriteAdaptor.h
 * @since 2017-03-22
 * @date 2017-05-10
 * @author Batis Degryll Ludo
 * @brief Adaptor that adapts an AnimatedDrawable to an AnimatedSprite.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ANIMATEDDRAWABLEANIMATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ANIMATEDDRAWABLEANIMATEDSPRITEADAPTOR_H_

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

  /** \brief Builds this adaptor with a AnimatedDrawable archetype.
   */
  AnimatedDrawableAnimatedSpriteAdaptor(AnimatedDrawable* entity): e(entity), s(nullptr) {}

  /** \brief Destroy this adaptor and the last alive avatar.
   */
  ~AnimatedDrawableAnimatedSpriteAdaptor() {delete s;}

  /** \brief Builds an AnimatedSprite a destroys the previous one.
   */
  AnimatedSprite* getAvatar() {
    delete s;
    s = new AnimatedSprite();

    s->x = e->getX();
    s->y = e->getY();
    s->graphics = e->getGraphics();
    s->degrees  = e->getDegrees();
    s->state    = e->getState();
    s->nstates  = e->getNumStates();
    s->frame    = e->getFrame();
    s->nframes  = e->getFArray();
    s->width    = e->getWArray();
    s->height   = e->getHArray();

    return (s);
  }

private:
	AnimatedDrawable* e;
	AnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ANIMATEDDRAWABLEANIMATEDSPRITEADAPTOR_H_
