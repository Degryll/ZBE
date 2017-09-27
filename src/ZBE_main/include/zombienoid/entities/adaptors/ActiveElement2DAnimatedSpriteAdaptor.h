/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ActiveElement2DAnimatedSpriteAdaptor.h
 * @since 2017-07-11
 * @date 2017-07-11
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_ACTIVEELEMENT2DANIMATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_ACTIVEELEMENT2DANIMATEDSPRITEADAPTOR_H_

#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/ActiveElement2D.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleAnimatedSprite.h"

namespace zbe {

/** \brief Implementation that adapts an ActiveElement2D to an AnimatedSprite.
 */
template <typename R>
class ActiveElement2DAnimatedSpriteAdaptor : public Adaptor<AnimatedSprite> {
public:
  ActiveElement2DAnimatedSpriteAdaptor(const ActiveElement2DAnimatedSpriteAdaptor&) = delete;
  void operator=(const ActiveElement2DAnimatedSpriteAdaptor&) = delete;

  ActiveElement2DAnimatedSpriteAdaptor(std::shared_ptr<ActiveElement2D<R> > entity): e(entity), s(nullptr) {
    double hw = e->getW()/2.0;
    double hh = e->getH()/2.0;
    s = new SimpleAnimatedSprite(e->getX()-hw, e->getY()-hh, e->getW(), e->getH(), e->getGraphics(), 0, e->getState(), e->getTimeStamp());
  }

  ~ActiveElement2DAnimatedSpriteAdaptor() {delete s;}

  AnimatedSprite* getAvatar() {
    s->setW(e->getW());
    s->setH(e->getH());
    s->setX(e->getX() - e->getW()/2.0);
    s->setY(e->getY() - e->getH()/2.0);
    return (s);
  }

private:
    std::shared_ptr<ActiveElement2D<R> > e;
    SimpleAnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_ACTIVEELEMENT2DANIMATEDSPRITEADAPTOR_H_
