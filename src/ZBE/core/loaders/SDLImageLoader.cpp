/*
 * SDLImageLoader.cpp
 *
 *  Created on: 17/08/2012
 *      Author: ludo
 */

#include "ZBE/core/loaders/SDLImageLoader.h"

namespace zbe {

SDLImageLoader* SDLImageLoader::_instance = NULL;

SDLImageLoader* SDLImageLoader::createInstance() {
  _instance = new SDLImageLoader;
  _instance->imgCollection.clear();
  return (_instance);
}

void SDLImageLoader::deleteInstance() {
  for(auto iter = _instance->imgCollection.begin(); iter != _instance->imgCollection.end(); iter++ ) {
    SDL_Surface* aux = iter->second;
    delete aux;
  }
  delete _instance;
}

SDLImageLoader* SDLImageLoader::getInstance() {
  return (_instance);
}

void zbe::SDLImageLoader::loadImg(const char *url, int id) {
  std::map<int,SDL_Surface*>::iterator it = imgCollection.find(id);
  if (it==imgCollection.end()) {
    imgCollection.insert(std::pair<int,SDL_Surface*>(id, IMG_Load(url)));
  }
}

void zbe::SDLImageLoader::reloadImg(const char *url, int id) {
  removeImg(id);
  imgCollection.insert(std::pair<int,SDL_Surface*>(id, IMG_Load(url)));
}

void zbe::SDLImageLoader::removeImg(int id) {
  std::map<int,SDL_Surface*>::iterator it = imgCollection.find(id);
  if (it!=imgCollection.end()) {
    SDL_Surface* aux = it->second;
    delete aux;
    imgCollection.erase(id);
  }
}


SDL_Surface* zbe::SDLImageLoader::getImg(int id) {
  std::map<int,SDL_Surface*>::iterator it = imgCollection.find(id);
  SDL_Surface* aux = 0;
  if (it!=imgCollection.end()) {
    aux = it->second;
  }
  return (aux);
}

}  // namespace zbe
