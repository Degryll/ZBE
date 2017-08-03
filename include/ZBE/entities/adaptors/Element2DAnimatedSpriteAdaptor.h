/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Element2DAnimatedSpriteAdaptor.h
 * @since 2017-07-06
 * @date 2017-07-06
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_

#include "ZBE/core/entities/avatars/implementations/SimpleSingleSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/core/entities/avatars/Element2D.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a AnimatedSprite.
 */
class Element2DAnimatedSpriteAdaptor : public Adaptor<AnimatedSprite> {
public:
  Element2DAnimatedSpriteAdaptor(const Element2DAnimatedSpriteAdaptor&) = delete;
  void operator=(const Element2DAnimatedSpriteAdaptor&) = delete;

  Element2DAnimatedSpriteAdaptor(Element2D* entity): e(entity), s(nullptr) {}

  ~Element2DAnimatedSpriteAdaptor() {delete s;}

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

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_
