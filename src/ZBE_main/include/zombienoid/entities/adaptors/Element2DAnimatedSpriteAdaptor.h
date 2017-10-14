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

  Element2DAnimatedSpriteAdaptor(std::weak_ptr<Element2D<R> > entity): e(entity), s(nullptr) {
    std::shared_ptr<Element2D<R> > ent = e.lock();
    s = new SimpleAnimatedSprite(ent->getX(), ent->getY(), ent->getW(), ent->getH(), ent->getGraphics(), 0, ent->getState(), ent->getTimeStamp());
  }

  ~Element2DAnimatedSpriteAdaptor() {delete s;}

  AnimatedSprite* getAvatar() {
    std::shared_ptr<Element2D<R> > ent = e.lock();
    double halfW = ent->getW() / 2.0;
    double halfH = ent->getH() / 2.0;
    s->setW(ent->getW());
    s->setH(ent->getH());
    s->setX(ent->getX() - halfW);
    s->setY(ent->getY() - halfH);
    s->setState(ent->getState());
    return (s);
  }

private:
    std::weak_ptr<Element2D<R> > e;
    SimpleAnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_ELEMENT2DANIMATEDSPRITEADAPTOR_H_

