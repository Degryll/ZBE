/**
 * Copyright 2012 Batis Degryll Ludo
 * @file RotatedDrawableRotatedSpriteAdaptor.h
 * @since 2017-03-22
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Template that adapts an RotatedDrawable to a RotatedSprite.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_ROTATEDDRAWABLEROTATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_ROTATEDDRAWABLEROTATEDSPRITEADAPTOR_H_

#include "ZBE/core/entities/avatars/RotatedSprite.h"
#include "ZBE/core/entities/Adaptor.h"

#include "ZBE/archetypes/RotatedDrawable.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Implementation that adapts an RotatedDrawable to a RotatedSprite.
 */
class ZBEAPI RotatedDrawableRotatedSpriteAdaptor : public Adaptor<RotatedSprite> {
public:
  RotatedDrawableRotatedSpriteAdaptor(const RotatedDrawableRotatedSpriteAdaptor&) = delete; //<! Avoid copy
  void operator=(const RotatedDrawableRotatedSpriteAdaptor&) = delete; //<! Avoid copy

  /** \brief Builds this adaptor with a RotatedDrawable archetype.
   */
  RotatedDrawableRotatedSpriteAdaptor(RotatedDrawable* entity): e(entity), s(nullptr) {}

  /** \brief Destroy this adaptor and the last alive avatar.
   */
  ~RotatedDrawableRotatedSpriteAdaptor() {delete s;}

  /** \brief Builds an RotatedSprite a destroys the previous one.
   */
  RotatedSprite* getAvatar() {
    delete s;
    s = new RotatedSprite(e->getX(), e->getY(), e->getW(), e->getH(), e->getGraphics(), e->getDegrees());

    return (s);
  }

private:
	RotatedDrawable* e;
	RotatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_ROTATEDDRAWABLEROTATEDSPRITEADAPTOR_H_
