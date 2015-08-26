/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2014-09-27
 * @author degryll
 * @brief Class that know how to draw SimpleSprite entities with SDL.
 */

#ifndef CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
#define CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_

#include "ZBE/core/drawers/Drawer.h"
#include "ZBE/core/archetypes/SimpleSprite.h"
#include "ZBE/core/SDL2.0/SDL_Window.h"

#include <SDL2/SDL.h>

//#include <forward_list>


namespace zbe {

//typedef std::forward_list<SimpleSprite*> flist;
//typedef std::forward_list<SimpleSprite*>::iterator iter;

typedef IteratorTypeErasure::any_iterator<
    SimpleSprite, // value type
    boost::forward_traversal_tag, // traversal tag. Note: std iterator categories are supported here
    SimpleSprite&, // reference type
    ptrdiff_t // difference type is irrelevant here, just don't use void, that'll throw the iterator_adaptor for a loop
  > SimpleSpriteIterator;

class SimpleSpriteSDLDrawer : public Drawer {
  public:
    SimpleSpriteSDLDrawer(SDL_Window* window, SimpleSpriteIterator first, SimpleSpriteIterator end) : window(window), firstSS(first), endSS(end) {}
    ~SimpleSpriteSDLDrawer() {}

    void draw();

  private:
    SDL_Window* window;
    SimpleSpriteIterator firstSS;
    SimpleSpriteIterator endSS;
};

}  // namespace zbe

#endif  // CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
