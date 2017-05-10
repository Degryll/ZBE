/**
 * Copyright 2012 Batis Degryll Ludo
 * @file StatedDrawableStatedSpriteAdaptor.h
 * @since 2017-03-22
 * @date 2017-05-10
 * @author Batis Degryll Ludo
 * @brief Template that adapts an StatedDrawable to a StatedSprite.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_STATEDDRAWABLESTATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_STATEDDRAWABLESTATEDSPRITEADAPTOR_H_

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

  /** \brief Builds this adaptor with a StatedDrawable archetype.
   */
  StatedDrawableStatedSpriteAdaptor(StatedDrawable* entity): e(entity), s(nullptr) {}

  /** \brief Destroy this adaptor and the last alive avatar.
   */
  ~StatedDrawableStatedSpriteAdaptor() {delete s;}

  /** \brief Builds an StatedSprite a destroys the previous one.
   */
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
