/**
 * Copyright 2010 Batis Degryll Ludo
 * @file SDL_Window.h
 *
 * @since 2015/05/30
 * @date 2017/06/11
 * @author Degryll Ludo
 * @brief Create a windows using SDL 2.0.
 */

#ifndef ZBE_SDL_SYSTEM_SDLWINDOW_H_
#define ZBE_SDL_SYSTEM_SDLWINDOW_H_

#include <vector>

#include <SDL2/SDL.h>

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/core/system/SysError.h"

namespace zbe {

/**
 * @class SDLWindow
 * @brief Used to create windows using SDL 2.0.
 */
class SDLWindow {
  public:
    SDLWindow(const SDLWindow&) = delete;  //!< Does not make sense to "copy" a SDLWindow.
    void operator=(const SDLWindow&) = delete;  //!< Does not make sense to "copy" a SDLWindow.

    /** \brief Creates a new SDLWindow and a default Renderer.
     *
     *  Creates a new SDLWindow and a Renderer with the size and flags specified.
     *  \param width Width of the Window.
     *  \param height Height of the Window.
     *  \param window_flags Flags for the SDLWindow creation. It creates a default Renderer. Default no flags.
     */
    SDLWindow(int width, int height, Uint32 window_flags = 0);

    /** \brief Creates a new SDLWindow and a Renderer.
     *
     *  Creates a new SDLWindow and a Renderer with the size and flags specified.
     *  \param title Title of the Window.
     *  \param width Width of the Window.
     *  \param height Height of the Window.
     *  \param window_flags Flags for the SDLWindow creation. Default no flags.
     *  \param rederer_flags Flags for the Renderer creation. Default no flags.
     */
    SDLWindow(const char* title, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0);

    /** \brief Creates a new SDLWindow and a Renderer in a specific position.
     *
     *  Creates a new SDLWindow and a Renderer with the position, size and flags specified.
     *  \param title Title of the Window.
     *  \param x X coordinates of the initial position of the window.
     *  \param y Y coordinates of the initial position of the window..
     *  \param width Width of the Window.
     *  \param height Height of the Window.
     *  \param window_flags Flags for the SDLWindow creation. Default no flags.
     *  \param rederer_flags Flags for the Renderer creation. Default no flags.
     */
    SDLWindow(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0);

    /** \brief Free resources and destroy the Renderer and the SDLWindow.
     */
    ~SDLWindow();

    /** \brief Clear the Renderer with the background color.
     *
     *  \sa setBackgroundColor()
     */
    void clear();

    /** \brief Set the background color.
     *
     *  \param red Red component of the color.
     *  \param green Green component of the color.
     *  \param blue Blue component of the color.
     *  \param alpha Alpha component of the color.
     *
     *  \sa clear()
     */
    inline void setBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
      if(SDL_SetRenderDrawColor(renderer, red, green, blue, alpha)) {
        zbe::SysError::setError(std::string("ERROR: SDL could not set the background color! SDL ERROR: ") + SDL_GetError());
      }
    }

//    /** \brief Draw the portion of the texture specified by srcrect in the portion of the SDLWindow specified by dstrect.
//     *
//     *  \param texID Id of the texture.
//     *  \param srcrect Portion of the texture to be drawn.
//     *  \param dstrect Portion of the SDLWindow where the texture is going to be drawn.
//     */
//    void render(uint64_t texID,const SDL_Rect* srcrect,const SDL_Rect* dstrect);
//
//    /** \brief Draw the portion of the texture specified by srcrect in the portion of the SDLWindow specified by dstrect.
//     *
//     *  This version can add some transformation to the drawing. Can rotate and flip the texture.
//     *
//     *  \param texID Id of the texture.
//     *  \param srcrect Portion of the texture to be drawn.
//     *  \param dstrect Portion of the SDLWindow where the texture is going to be drawn.
//     *  \param angle Angle to rotate the texture.
//     *  \param center A SDL_Point pointer that represents the center of rotation of the texture. if null, the center of dstrect will be used.
//     *  \param flip A SDL_RendererFlip with the values SDL_FLIP_NONE (do not flip), SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL or diagonal flip (both horizontal and vertical), use bitwise or ('|' operator).
//     */
//    void render(uint64_t texID,const SDL_Rect* srcrect,const SDL_Rect* dstrect,const double angle,const SDL_Point* center,const SDL_RendererFlip flip = SDL_FLIP_NONE);

    /** \brief Draw the portion of the texture received by srcrect in the portion of the SDLWindow specified by dstrect.
     *
     *  \param tex Texture.
     *  \param srcrect Portion of the texture to be drawn.
     *  \param dstrect Portion of the SDLWindow where the texture is going to be drawn.
     */
    void render(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect);

    /** \brief Draw the portion of the texture received in the portion of the SDLWindow specified by dstrect.
     *
     *  This version can add some transformation to the drawing. Can rotate and flip the texture.
     *
     *  \param tex Texture.
     *  \param srcrect Portion of the texture to be drawn.
     *  \param dstrect Portion of the SDLWindow where the texture is going to be drawn.
     *  \param angle Angle to rotate the texture.
     *  \param center A SDL_Point pointer that represents the center of rotation of the texture. if null, the center of dstrect will be used.
     *  \param flip A SDL_RendererFlip with the values SDL_FLIP_NONE (do not flip), SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL or diagonal flip (both horizontal and vertical), use bitwise or ('|' operator).
     */
    void render(SDL_Texture* tex, const SDL_Rect* srcrect,const SDL_Rect* dstrect,const double angle,const SDL_Point* center,const SDL_RendererFlip flip = SDL_FLIP_NONE);

    /** \brief Draw the portion of the texture received (as a surface) by srcrect in the portion of the SDLWindow specified by dstrect.
     *
     *  \param surf Surface.
     *  \param srcrect Portion of the texture to be drawn.
     *  \param dstrect Portion of the SDLWindow where the texture is going to be drawn.
     */
    void render(SDL_Surface* surf, const SDL_Rect* srcrect, const SDL_Rect* dstrect);

    /** \brief Draw the portion of the texture received (as a surface) in the portion of the SDLWindow specified by dstrect.
     *
     *  This version can add some transformation to the drawing. Can rotate and flip the texture.
     *
     *  \param surf Surface.
     *  \param srcrect Portion of the texture to be drawn.
     *  \param dstrect Portion of the SDLWindow where the texture is going to be drawn.
     *  \param angle Angle to rotate the texture.
     *  \param center A SDL_Point pointer that represents the center of rotation of the texture. if null, the center of dstrect will be used.
     *  \param flip A SDL_RendererFlip with the values SDL_FLIP_NONE (do not flip), SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL or diagonal flip (both horizontal and vertical), use bitwise or ('|' operator).
     */
    void render(SDL_Surface* surf, const SDL_Rect* srcrect,const SDL_Rect* dstrect,const double angle,const SDL_Point* center,const SDL_RendererFlip flip = SDL_FLIP_NONE);

    /** \brief Return the internal render.
     *  \return The internal render.
     */
    SDL_Renderer* getRenderer() {return renderer;}

//    /** \brief Creates a texture from a text and a font. Draw the portion of this texture specified by srcrect in the portion of the SDLWindow specified by dstrect.
//     *  \param fontID The ID of the font.
//     *  \param text The text.
//     *  \param srcrect Portion of the texture to be drawn.
//     *  \param dstrect Portion of the SDLWindow where the texture is going to be drawn.
//     */
//    void render(uint64_t fontID, const char *text, const SDL_Rect* srcrect, const SDL_Rect* dstrect);
//
//     /** \brief Draw the portion of the texture received (as a surface) in the portion of the SDLWindow specified by dstrect.
//     *
//     *  This version can add some transformation to the drawing. Can rotate and flip the texture.
//     *
//     *  \param fontID The ID of the font.
//     *  \param text The text.
//     *  \param srcrect Portion of the texture to be drawn.
//     *  \param dstrect Portion of the SDLWindow where the texture is going to be drawn.
//     *  \param angle Angle to rotate the texture.
//     *  \param center A SDL_Point pointer that represents the center of rotation of the texture. if null, the center of dstrect will be used.
//     *  \param flip A SDL_RendererFlip with the values SDL_FLIP_NONE (do not flip), SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL or diagonal flip (both horizontal and vertical), use bitwise or ('|' operator).
//     */
//    void render(uint64_t fontID, const char *text, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip);

    /** \brief Update the SDLWindow. Similar to swapbuffers in a double buffer rendering.
     */
    void present() {SDL_RenderPresent(renderer);}

    void render2Texture() {
      SDL_SetRenderTarget(renderer, output);
    }

    void render2Screen() {
      SDL_SetRenderTarget(renderer, nullptr);
    }

    void readPixels(char* data, int pitch) {
      SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_BGR888, data, pitch);
    }

  private:
    SDL_Starter &sdl;                         //!< SDL instance.
    SDL_Window* window;                       //!< Window.
    SDL_Renderer* renderer;                   //!< Renderer associated with the window
    SDL_Texture* output;                      //!< Output texture.
};

}  // namespace zbe

#endif  // ZBE_SDL_SYSTEM_SDLWINDOW_H_
