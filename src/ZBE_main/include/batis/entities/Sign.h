 /**
 * Copyright 2012 Batis Degryll Ludo
 * @file Sign.h
 * @since 2017-04-13
 * @date 2017-04-16
 * @author Batis
 * @brief A SIGN, MILKS.
 */

#ifndef BATIS_ENTITIES_SIGN
#define BATIS_ENTITIES_SIGN

#include <SDL2/SDL_ttf.h>

#include "batis/archetypes/TextDrawable.h"
#include "batis/entities/avatars/SingleTextSprite.h"
#include "ZBE/core/entities/AvatarEntity.h"

namespace batis{

class Sign: public zbe::TextDrawable, public zbe::AvatarEntityAdapted<zbe::SingleTextSprite> {

public:
  Sign(const Sign&) = delete;
  void operator=(const Sign&) = delete;

  Sign(int64_t x, int64_t y, int64_t w, int64_t h, uint64_t font, const char *text) : x(x), y(y), w(w), h(h), f(font), text(text) {
     //call TTF_SizeText(TTF_Font *font, const char *text, int *w, int *h) to averiguar el tamaño;
  }

  int64_t getX() {return (x);}
  int64_t getY() {return (y);}
  int64_t getW() {return (w);}
  int64_t getH() {return (h);}
  uint64_t getGraphics() {return (f);}
  const char* getText() {return (text);}

private:
  int64_t  x;       //!< X position
  int64_t  y;       //!< Y position
  int64_t  w;       //!< Width
  int64_t  h;       //!< Height
  uint64_t f;       //!< Font index
  const char* text; //!< Text to draw

};

}  // namespace batis

#endif // BATIS_ENTITIES_SIGN
