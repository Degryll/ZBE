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

#include "ZBE/core/system/SysTime.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/entities/ActiveElement2D.h"
#include "ZBE/core/entities/avatars/AnimatedSprite.h"
#include "ZBE/core/entities/avatars/implementations/SimpleAnimatedSprite.h"

namespace zombienoid {

/** \brief Implementation that adapts an ActiveElement2D to an AnimatedSprite.
 */
template <typename R>
class ActiveElement2DAnimatedSpriteAdaptor : public zbe::Adaptor<zbe::AnimatedSprite> {
public:
  ActiveElement2DAnimatedSpriteAdaptor(const ActiveElement2DAnimatedSpriteAdaptor&) = delete;
  void operator=(const ActiveElement2DAnimatedSpriteAdaptor&) = delete;

  ActiveElement2DAnimatedSpriteAdaptor(std::weak_ptr<zbe::ActiveElement2D<R> > entity): e(entity), s(nullptr), contextTime(zbe::SysTime::getInstance()) {
    std::shared_ptr<zbe::ActiveElement2D<R> > ent = e.lock();
    double hw = ent->getW()/2.0;
    double hh = ent->getH()/2.0;
    s = new zbe::SimpleAnimatedSprite(ent->getX()-hw, ent->getY()-hh, ent->getW(), ent->getH(), ent->getGraphics(), 0, ent->getState(), ent->getTimeStamp());
  }

  ~ActiveElement2DAnimatedSpriteAdaptor() {delete s;}

  zbe::AnimatedSprite* getAvatar() {
    std::shared_ptr<zbe::ActiveElement2D<R> > ent = e.lock();
    s->setW(ent->getW());
    s->setH(ent->getH());
    s->setX(ent->getX() - ent->getW()/2.0);
    s->setY(ent->getY() - ent->getH()/2.0);
    s->setState(ent->getState());
    s->setTime(contextTime->getTotalTime());
    return (s);
  }

private:
    std::weak_ptr<zbe::ActiveElement2D<R> > e;
    zbe::SimpleAnimatedSprite* s;
    std::shared_ptr<zbe::ContextTime> contextTime;
};

}  // namespace zombienoid

#endif  // ZBE_ENTITIES_ADAPTORS_ACTIVEELEMENT2DANIMATEDSPRITEADAPTOR_H_
