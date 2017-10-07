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

  ActiveElement2DAnimatedSpriteAdaptor(std::weak_ptr<ActiveElement2D<R> > entity): e(entity), s(nullptr) {
    std::shared_ptr<ActiveElement2D<R> > ent = e.lock();
    double hw = ent->getW()/2.0;
    double hh = ent->getH()/2.0;
    s = new SimpleAnimatedSprite(ent->getX()-hw, ent->getY()-hh, ent->getW(), ent->getH(), ent->getGraphics(), 0, ent->getState(), ent->getTimeStamp());
  }

  ~ActiveElement2DAnimatedSpriteAdaptor() {delete s;}

  AnimatedSprite* getAvatar() {
    std::shared_ptr<ActiveElement2D<R> > ent = e.lock();
    s->setW(ent->getW());
    s->setH(ent->getH());
    s->setX(ent->getX() - ent->getW()/2.0);
    s->setY(ent->getY() - ent->getH()/2.0);
    return (s);
  }

private:
    std::weak_ptr<ActiveElement2D<R> > e;
    SimpleAnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_ACTIVEELEMENT2DANIMATEDSPRITEADAPTOR_H_
