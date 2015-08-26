/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSprite.h
 * @since 2014-09-27
 * @date 2015-05-04
 * @author Ludo and Degryll
 * @brief Define a class that can be draw as a simple sprite.
 */

#ifndef CORE_ARCHETYPES_SIMPLESPRITE_H_
#define CORE_ARCHETYPES_SIMPLESPRITE_H_

#include <SDL2/SDL.h>

namespace zbe {

class SimpleSprite {
  public:
    SimpleSprite() : x(0), y(0), w(0), h(0), img(0) {}
    SimpleSprite(unsigned width, unsigned height, SDL_Surface* img) : x(0), y(0), w(width), h(height), img(img) {}
    SimpleSprite(int x, int y,unsigned width, unsigned height, SDL_Surface* img) : x(x), y(y), w(width), h(height), img(img) {}

    ~SimpleSprite() {}

    inline void setLeftX(int x)            {this->x = x;}
    inline void setTopY(int y)             {this->y = y;}
    inline void setWidth(unsigned width)   {this->w = width;}
    inline void setHeight(unsigned height) {this->h = height;}
    inline void setImage(unsigned img)     {this->img = img;}

    inline int      getLeftX()  const {return (x);}
    inline int      getTopY()   const {return (y);}
    inline unsigned getWidth()  const {return (w);}
    inline unsigned getHeight() const {return (h);}
    inline unsigned getImage()  const {return (img);}

  private:
    int x = 0;
    int y = 0;
    unsigned w = 0;
    unsigned h = 0;
    unsigned img = 0;
};

}  // namespace zbe

#endif  // CORE_ARCHETYPES_SIMPLESPRITE_H_
