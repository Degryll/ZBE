/**
 * Copyright 2012 Batis Degryll Ludo
 * @file TextDrawableSingleTextSpriteAdaptor.h
 * @since 2017-04-16
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Template that adapts an entity to a SingleTextSprite.
 */

#ifndef ZBE_ENTITIES_ADAPTORS_TEXTDRAWABLESINGLETEXTSPRITEADAPTOR_H_
#define ZBE_ENTITIES_ADAPTORS_TEXTDRAWABLESINGLETEXTSPRITEADAPTOR_H_

#include "ZBE/entities/avatars/SingleTextSprite.h"
#include "ZBE/core/entities/Adaptor.h"
#include "ZBE/archetypes/TextDrawable.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Implementation that adapts an Drawable to a SingleSprite.
 */
class ZBEAPI TextDrawableSingleTextSpriteAdaptor : public Adaptor<SingleTextSprite> {
public:
  TextDrawableSingleTextSpriteAdaptor(const TextDrawableSingleTextSpriteAdaptor&) = delete;
  void operator=(const TextDrawableSingleTextSpriteAdaptor&) = delete;

  /** \brief Builds this adaptor with a TextDrawable archetype.
   */
  TextDrawableSingleTextSpriteAdaptor(TextDrawable* entity): e(entity), s(nullptr) {}

  /** \brief Destroy this adaptor and the last alive avatar.
   */
  ~TextDrawableSingleTextSpriteAdaptor() {delete s;}

  /** \brief Builds an SingleTextSprite a destroys the previous one.
   */
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

#endif  // ZBE_ENTITIES_ADAPTORS_TEXTDRAWABLESINGLETEXTSPRITEADAPTOR_H_
