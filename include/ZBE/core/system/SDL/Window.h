/*
 * Copyright 2010 Batis Degryll Ludo
 * @file SDL_Window.h
 *
 * @since 2015/05/30
 * @date 2015/05/30
 * @author Degryll
 * @brief Create a windows using SDL 2.0.
 */

#ifndef SRC_SDL_WINDOW_H_
#define SRC_SDL_WINDOW_H_

#include <vector>
#include <mutex>

#include <SDL2/SDL.h>

namespace zbe {

/**
 * @class Window
 * @brief Used to create windows using SDL 2.0.
 */
class Window {
  public:
    Window(int width, int height, Uint32 window_flags = 0);
    Window(const char* title, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0);
    Window(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0);

    ~Window();

    void clear();

    void render(SDL_Texture* texture,const SDL_Rect* srcrect,const SDL_Rect* dstrect);
    void render(SDL_Texture* texture,const SDL_Rect* srcrect,const SDL_Rect* dstrect,const double angle,const SDL_Point* center,const SDL_RendererFlip flip);

    void render(unsigned texID,const SDL_Rect* srcrect,const SDL_Rect* dstrect);
    void render(unsigned texID,const SDL_Rect* srcrect,const SDL_Rect* dstrect,const double angle,const SDL_Point* center,const SDL_RendererFlip flip);

    void present() {SDL_RenderPresent(renderer);}

    unsigned loadImg(const char *url);
    unsigned reloadImg(const char *url, unsigned id);

  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> imgCollection;
    std::mutex m;
};

}  // namespace zbe

#endif  // SRC_SDL_WINDOW_H_
