/*
 * SDLImageLoader.h
 *
 *  Created on: 17/08/2012
 *      Author: ludo
 */

#ifndef CORE_LOADERS_SDLIMAGELOADER_H_
#define CORE_LOADERS_SDLIMAGELOADER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// TODO Degryll cambiar a una estructura en la que el acceso a un elemento sea O(1).
#include <map>

namespace zbe {

/*
 *
 */
class SDLImageLoader {
  public:
    static SDLImageLoader* createInstance();
    static void    deleteInstance();
    static SDLImageLoader* getInstance();

    void loadImg(const char *url, int id);
    void reloadImg(const char *url, int id);
    void removeImg(int id);

    SDL_Surface* getImg(int id);

  private:
    static SDLImageLoader* _instance;

    std::map<int,SDL_Surface*> imgCollection;

    SDLImageLoader() {}
};

}  // namespace zbe

#endif  // CORE_LOADERS_SDLIMAGELOADER_H_
