/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Element2DAnimatedSpriteAdaptor.h
 * @since 2017-07-11
 * @date 2017-07-11
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_

#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/Element2D.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

namespace zbe {

/** \brief Implementation that adapts an Element2D to an AnimatedSprite.
 */
template <typename R>
class Element2DAnimatedSpriteAdaptor : public Adaptor<AnimatedSprite> {
public:
  Element2DAnimatedSpriteAdaptor(const Element2DAnimatedSpriteAdaptor&) = delete;
  void operator=(const Element2DAnimatedSpriteAdaptor&) = delete;

  Element2DAnimatedSpriteAdaptor(Element2D<R>* entity): e(entity), s(nullptr) {}

  ~Element2DAnimatedSpriteAdaptor() {delete s;}

  AnimatedSprite* getAvatar() {
    delete s;
    s = new SimpleAnimatedSprite(e->getX(), e->getY(), e->getW(), e->getH(), e->getGraphics(), 0, e->getState(), e->getTimeStamp());
    return (s);
  }

private:
    Element2D<R>* e;
    AnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_
