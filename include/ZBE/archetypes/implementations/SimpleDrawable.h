/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleDrawable.h
 * @since 2016-11-22
 * @date 2016-11-22
 * @author Degryll
 * @brief This implements an entity that can be drawn.
 */

#ifndef ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDRAWABLE_H_
#define ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDRAWABLE_H_

#include "ZBE/archetypes/Drawable.h"

namespace zbe {

/** \brief This implements an entity that can be drawn.
 */
class SimpleDrawable : public Drawable {
  public:
    SimpleDrawable(int x, int y, unsigned w, unsigned h, int graphics) : x(x), y(y), w(w), h(h), graphics(graphics) {}

    virtual ~SimpleDrawable() {}

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

#endif  // ZBE_ARCHETYPES_IMPLEMENTATIONS_SIMPLEDRAWABLE_H_
