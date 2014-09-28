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
#include "ZBE/core/loaders/SDLImageLoader.h"

#include <SDL2/SDL.h>

#include <forward_list>


namespace zbe {

typedef std::forward_list<SimpleSprite*> flist;
typedef std::forward_list<SimpleSprite*>::iterator iter;

class SimpleSpriteSDLDrawer : public Drawer {
  public:
    SimpleSpriteSDLDrawer(SDL_Surface *image);
    SimpleSpriteSDLDrawer(SDL_Surface *image, flist *forwardlist);
    virtual ~SimpleSpriteSDLDrawer();

    iter add(SimpleSprite *entitie);

    void draw();

  private:
    SDL_Surface *image;
    flist *l;
    bool d;
    iter i;
    SDLImageLoader* sdll;
};

}  // namespace zbe

#endif  // CORE_DRAWERS_SIMPLESPRITESDLDRAWER_H_
