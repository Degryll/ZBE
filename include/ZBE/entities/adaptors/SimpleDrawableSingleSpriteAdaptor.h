/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleDrawableSingleSpriteAdaptor.h
 * @since 2017-03-22
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a drawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_SIMPLEDRAWABLESINGLESPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_SIMPLEDRAWABLESINGLESPRITEADAPTOR_H_

#include <memory>

#include "ZBE/core/entities/avatars/implementations/SimpleSingleSprite.h"
#include "ZBE/core/entities/avatars/SingleSprite.h"
#include "ZBE/core/entities/Adaptor.h"

#include "ZBE/archetypes/Drawable.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a SingleSprite.
 */
class SimpleDrawableSingleSpriteAdaptor : public Adaptor<SingleSprite> {
public:
  SimpleDrawableSingleSpriteAdaptor(const SimpleDrawableSingleSpriteAdaptor&) = delete; //<! Avoid copy
  void operator=(const SimpleDrawableSingleSpriteAdaptor&) = delete; //<! Avoid copy

  /** \brief Constructs a SimpleDrawableSingleSpriteAdaptor with an Drawable.
   */
  SimpleDrawableSingleSpriteAdaptor(std::weak_ptr<Drawable> entity): e(entity), s(nullptr) {}

  /** \brief Virtual destructor.
   */
  ~SimpleDrawableSingleSpriteAdaptor() {delete s;}

  /** \brief Return an SingleSprite avatar.
   *  \return SingleSprite avatar.
   */
  SingleSprite* getAvatar() {
    delete s;
    std::shared_ptr<Drawable> ent = e.lock();
    s = new SimpleSingleSprite(ent->getX(),ent->getY(),ent->getW(),ent->getH(),ent->getGraphics());

    return (s);
  }

private:
	std::weak_ptr<Drawable> e;
	SingleSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_SIMPLEDRAWABLESINGLESPRITEADAPTOR_H_
