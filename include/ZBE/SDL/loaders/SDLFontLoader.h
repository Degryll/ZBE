/*
 * SDLFontLoader.h
 *
 *  Created on: 17/08/2012
 *      Author: ludo
 */

#ifndef CORE_LOADERS_SDLFONTLOADER_H_
#define CORE_LOADERS_SDLFONTLOADER_H_

//#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// TODO Degryll cambiar a una estructura en la que el acceso a un elemento sea O(1).
#include <map>

namespace zbe {

/*
 *
 */
class SDLFontLoader {
  public:
    static SDLFontLoader* createInstance();
    static void    deleteInstance();
    static SDLFontLoader* getInstance();

    void loadFont(const char *url,int size, int id);
    void reloadFont(const char *url,int size, int id);
    void removeFont(int id);

    TTF_Font* getFont(int id);

  private:
    static SDLFontLoader* _instance;

    std::map<int,TTF_Font*> fontCollection;

    SDLFontLoader() : fontCollection() {}
};

}  // namespace zbe

#endif  // CORE_LOADERS_SDLFONTLOADER_H_
