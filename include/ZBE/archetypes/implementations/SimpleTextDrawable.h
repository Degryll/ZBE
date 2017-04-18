/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleTextDrawable.h
 * @since 2017-16-16
 * @date 2017-16-16
 * @author Batis
 * @brief This implements an entity that can be wrote.
 */

#ifndef ZBE_MAIN_BATIS_ARCHETYPES_IMPLEMENTATIONS_SIMPLETEXTDRAWABLE_H_
#define ZBE_MAIN_BATIS_ARCHETYPES_IMPLEMENTATIONS_SIMPLETEXTDRAWABLE_H_

#include "ZBE/archetypes/Drawable.h"

namespace zbe {

/** \brief This implements an entity that can be wrote.
 */
class SimpleTextDrawable : virtual public Drawable {
  public:
    SimpleTextDrawable(int x, int y, unsigned w, unsigned h, int graphics, const char* text, TTF_Font* font, SDL_Color* color) : x(x), y(y), w(w), h(h), graphics(graphics) {}

    virtual ~SimpleTextDrawable() {}

    int      getX()        {return (x);}
    int      getY()        {return (y);}
    unsigned getW()        {return (w);}
    unsigned getH()        {return (h);}
    int      getGraphics() {return (graphics);}

    void setX(int x)               {this->x = x;}
    void setY(int y)               {this->y = y;}
    void setW(unsigned w)          {this->w = w;}
    void setH(unsigned h)          {this->h = h;}
    void setGraphics(int graphics) {this->graphics = graphics;}

  private:
    int x;      //!< X coordinate
    int y;      //!< Y coordinate
    unsigned w; //!< width
    unsigned h; //!< height
    int graphics;    //!< Image index
};

}  // namespace zbe

#endif  // ZBE_MAIN_BATIS_ARCHETYPES_IMPLEMENTATIONS_SIMPLETEXTDRAWABLE_H_
