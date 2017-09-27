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

  Element2DAnimatedSpriteAdaptor(std::shared_ptr<Element2D<R> > entity): e(entity), s(nullptr) {
    s = new SimpleAnimatedSprite(e->getX(), e->getY(), e->getW(), e->getH(), e->getGraphics(), 0, e->getState(), e->getTimeStamp());
  }

  ~Element2DAnimatedSpriteAdaptor() {delete s;}

  AnimatedSprite* getAvatar() {
    s->setW(e->getW());
    s->setH(e->getH());
    s->setX(e->getX());
    s->setY(e->getY());
    s->setState(e->getState());
    return (s);
  }

private:
    std::shared_ptr<Element2D<R> > e;
    SimpleAnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_

