/**
 * Copyright 2012 Batis Degryll Ludo
 * @file BaseSingleTextSprite.h
 * @since 2017-08-22
 * @date 2017-08-22
 * @author Batis Degryll Ludo
 * @brief Base implementation of a single text sprite.
 */

#ifndef ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESINGLETEXTSPRITE_H_
#define ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESINGLETEXTSPRITE_H_

#include <cstdint>

#include "ZBE/entities/avatars/SingleTextSprite.h"

#include "ZBE/archetypes/TextDrawable.h"

namespace zbe {

/** \brief Base implementation of a single text sprite.
 */
class BaseSingleTextSprite : virtual public SingleTextSprite {
public:
  BaseSingleTextSprite(const BaseSingleTextSprite&) = delete; //<! Avoid copy
  void operator=(const BaseSingleTextSprite&) = delete; //<! Avoid copy

  BaseSingleTextSprite(TextDrawable* textDrawable) : td(textDrawable) {}

  /** \brief Virtual Destructor.
   */
  ~BaseSingleTextSprite(){};

  /** \brief Returns x.
   *  \return x.
   */
  int64_t getX() {return (td->getX());}

  /** \brief Returns y.
   *  \return y.
   */
  int64_t getY() {return (td->getY());}

  /** \brief Returns w.
   *  \return w.
   */
  int64_t getW() {return (td->getW());}

  /** \brief Returns h.
   *  \return h.
   */
  int64_t getH() {return (td->getH());}

  /** \brief Returns text.
   *  \return text.
   */
  const std::string& getText() {return (td->getText());}

  /** \brief Returns graphics.
   *  \return graphics.
   */
  int64_t getGraphics() {return (td->getGraphics());}

private:

  TextDrawable* td; //<! Text drawable with the desired data.

};

}  // namespace zbe

#endif  // ZBE_ENTITIES_AVATARS_IMPLEMENTATIONS_BASESINGLETEXTSPRITE_H_