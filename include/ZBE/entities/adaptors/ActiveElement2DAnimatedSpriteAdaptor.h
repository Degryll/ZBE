/**
 * Copyright 2012 Batis Degryll Ludo
 * @file ActiveElement2DAnimatedSpriteAdaptor.h
 * @since 2017-07-06
 * @date 2017-07-06
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ACTIVEELEMENT2DANIMATEDSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ACTIVEELEMENT2DANIMATEDSPRITEADAPTOR_H_

#include "ZBE/core/entities/avatars/implementations/SimpleSingleSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/core/entities/avatars/ActiveElement2D.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a AnimatedSprite.
 */
class ActiveElement2DAnimatedSpriteAdaptor : public Adaptor<AnimatedSprite> {
public:
  ActiveElement2DAnimatedSpriteAdaptor(const ActiveElement2DAnimatedSpriteAdaptor&) = delete;
  void operator=(const ActiveElement2DAnimatedSpriteAdaptor&) = delete;

  ActiveElement2DAnimatedSpriteAdaptor(ActiveElement2D* entity): e(entity), s(nullptr) {}

  ~ActiveElement2DAnimatedSpriteAdaptor() {delete s;}

  AnimatedSprite* getAvatar() {

    delete s;
    s = new SimpleAnimatedSprite(e->getX(),e->getY(),e->getW(),e->getH(),e->getGraphics(), e->getVelocity().getDegrees(), e->getState(), e->getTime());

    return (s);
  }

private:
    ActiveElement2D* e;
    AnimatedSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_ACTIVEELEMENT2DANIMATEDSPRITEADAPTOR_H_
