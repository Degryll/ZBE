/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TextDrawableSingleTextSpriteAdaptor.h
 * @since 2017-04-16
 * @date 2017-04-16
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a textDrawable.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_TEXTDRAWABLESINGLETEXTSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_TEXTDRAWABLESINGLETEXTSPRITEADAPTOR_H_

#include <memory>

#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/TextDrawable.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a SingleSprite.
 */
class TextDrawableSingleTextSpriteAdaptor : public Adaptor<SingleTextSprite> {
public:
  TextDrawableSingleTextSpriteAdaptor(const TextDrawableSingleTextSpriteAdaptor&) = delete;
  void operator=(const TextDrawableSingleTextSpriteAdaptor&) = delete;

  TextDrawableSingleTextSpriteAdaptor(TextDrawable* entity): e(entity), s(nullptr) {}
  ~TextDrawableSingleTextSpriteAdaptor() {delete s;}
    SingleTextSprite* getAvatar() {
      delete s;
      s = new SingleTextSprite();

      s->x = e->getX();
      s->y = e->getY();
      s->w = e->getW();
      s->h = e->getH();
      s->graphics = e->getGraphics();
      s->text = e->getText();

      return (s);
    }

private:
    TextDrawable* e;
    SingleTextSprite* s;
};

}  // namespace zbe

#endif  // ZBE_ENTITIES_ADAPTORS_IMPLEMENTATIONS_TEXTDRAWABLESINGLETEXTSPRITEADAPTOR_H_
