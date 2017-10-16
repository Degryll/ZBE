/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Element2DDisplacedAnimatedSpriteAdaptor.h
 * @since 2017-07-11
 * @date 2017-07-11
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_ELEMENT2DDISPLACEDANIMATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_ELEMENT2DDISPLACEDANIMATEDSPRITEADAPTOR_H_

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/Element2D.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"

namespace zbe {

/** \brief Implementation that adapts an Element2D to an AnimatedSprite.
 */
template <typename R>
class Element2DDisplacedAnimatedSpriteAdaptor : public Adaptor<AnimatedSprite> {
public:
  Element2DDisplacedAnimatedSpriteAdaptor(const Element2DDisplacedAnimatedSpriteAdaptor&) = delete;
  void operator=(const Element2DDisplacedAnimatedSpriteAdaptor&) = delete;

  Element2DDisplacedAnimatedSpriteAdaptor(std::weak_ptr<Element2D<R> > entity, zbe::Vector2D displacement): e(entity), s(nullptr), d(displacement), sysTime(zbe::SysTime::getInstance()) {
    std::shared_ptr<Element2D<R> > ent = e.lock();
    s = new SimpleAnimatedSprite(ent->getX(), ent->getY(), ent->getW(), ent->getH(), ent->getGraphics(), 0, ent->getState(), ent->getTimeStamp());
  }

  ~Element2DDisplacedAnimatedSpriteAdaptor() {delete s;}

  AnimatedSprite* getAvatar() {
    std::shared_ptr<Element2D<R> > ent = e.lock();
    s->setW(ent->getW());
    s->setH(ent->getH());
    s->setX(ent->getX() + d.x);
    s->setY(ent->getY() + d.y);
    s->setState(ent->getState());
    s->setTime(sysTime.getTotalTime());
    return (s);
  }

private:
    std::weak_ptr<Element2D<R> > e;
    SimpleAnimatedSprite* s;
    zbe::Vector2D d;
    zbe::SysTime &sysTime;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_ELEMENT2DDISPLACEDANIMATEDSPRITEADAPTOR_H_

