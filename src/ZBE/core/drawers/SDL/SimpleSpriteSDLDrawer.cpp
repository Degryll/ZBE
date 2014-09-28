/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleSpriteSDLDrawer.h
 * @since 2012-02-01
 * @date 2014-09-27
 * @author degryll
 * @brief Class that know how to draw ball Entities
 *        for the game ZombieBall.
 */

#include "ZBE/core/drawers/SDL/SimpleSpriteSDLDrawer.h"

namespace zbe {

SimpleSpriteSDLDrawer::SimpleSpriteSDLDrawer(SDL_Surface *image) : image(image), d(true) {
  l = new flist;
  i = l->before_begin();
  sdll = SDLImageLoader::getInstance();
}

SimpleSpriteSDLDrawer::SimpleSpriteSDLDrawer(SDL_Surface *image, flist *forwardlist) : image(image), l(forwardlist), d(false) {
  i = l->before_begin();
  for(auto it = l->begin(); it != l->end(); ++it) {
    i = it;
  }
  sdll = SDLImageLoader::getInstance();
}

SimpleSpriteSDLDrawer::~SimpleSpriteSDLDrawer(){
  if(d) delete l;
}

iter SimpleSpriteSDLDrawer::add(SimpleSprite *entitie) {
  iter aux = i;
  i = l->insert_after(i,entitie);
  return aux;
}

void SimpleSpriteSDLDrawer::draw() {
  SDL_Rect src,dst;
  src.x = 0;
  src.y = 0;
  for(auto it = l->begin(); it != l->end(); ++it) {
    SimpleSprite *entitie = *it;
    src.w = entitie->getWidth();
    src.h = entitie->getHeight();

    dst.x = entitie->getLeftX();
    dst.y = entitie->getTopY();
    dst.w = entitie->getWidth();
    dst.h = entitie->getHeight();
    SDL_BlitSurface(sdll->getImg(entitie->getImage()), &src, image, &dst);
  }
}

}  // namespace zbe
