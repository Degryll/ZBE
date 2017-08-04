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

  ActiveElement2DAnimatedSpriteAdaptor(ActiveElement2D<R>* entity): e(entity), s(nullptr) {}

  ~ActiveElement2DAnimatedSpriteAdaptor() {delete s;}

  AnimatedSprite* getAvatar() {

    delete s;

    s = new SimpleAnimatedSprite(e->getX(), e->getY(), e->getW(), e->getH(), e->getGraphics(), 0, e->getState(), e->getTimeStamp());


    return (s);
  }

private:
    ActiveElement2D<R>* e;
    AnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_ACTIVEELEMENT2DANIMATEDSPRITEADAPTOR_H_
