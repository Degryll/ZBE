/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Element2DAnimatedSpriteAdaptor.h
 * @since 2017-07-06
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_

#include "ZBE/core/entities/avatars/implementations/SimpleAnimatedSprite.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/core/entities/avatars/Element2D.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a AnimatedSprite.
 */
class Element2DAnimatedSpriteAdaptor : public Adaptor<AnimatedSprite> {
public:
  Element2DAnimatedSpriteAdaptor(const Element2DAnimatedSpriteAdaptor&) = delete; //<! Avoid copy
  void operator=(const Element2DAnimatedSpriteAdaptor&) = delete; //<! Avoid copy

  /** \brief Constructs a Element2DAnimatedSpriteAdaptor with an Element2D.
   */
  Element2DAnimatedSpriteAdaptor(Element2D* entity): e(entity), s(nullptr) {}

  /** \brief Virtual destructor.
   */
  ~Element2DAnimatedSpriteAdaptor() {delete s;}

  /** \brief Return an AnimatedSprite avatar.
   *  \return AnimatedSprite avatar.
   */
  AnimatedSprite* getAvatar() {

    delete s;
    s = new SimpleAnimatedSprite(e->getX(),e->getY(),e->getW(),e->getH(),e->getGraphics(), 0.0, e->getState(), e->getTime());

    return (s);
  }

private:
    Element2D* e;
    AnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_
