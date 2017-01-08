/**
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

#include "ZBE/SDL/starters/SDL_Starter.h"

namespace zbe {

/**
 * @class Window
 * @brief Used to create windows using SDL 2.0.
 */
class Window {
  public:
    Window(const Window&) = delete;  //!< Does not make sense to "copy" a Window.

    /** \brief Creates a new Window and a default Renderer.
     *
     *  Creates a new Window and a Renderer with the size and flags specified.
     *  \param width Width of the Window.
     *  \param height Height of the Window.
     *  \param window_flags Flags for the Window creation. It creates a default Renderer. Default no flags.
     */
    Window(int width, int height, Uint32 window_flags = 0);

    /** \brief Creates a new Window and a Renderer.
     *
     *  Creates a new Window and a Renderer with the size and flags specified.
     *  \param title Title of the Window.
     *  \param width Width of the Window.
     *  \param height Height of the Window.
     *  \param window_flags Flags for the Window creation. Default no flags.
     *  \param rederer_flags Flags for the Renderer creation. Default no flags.
     */
    Window(const char* title, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0);

    /** \brief Creates a new Window and a Renderer in a specific position.
     *
     *  Creates a new Window and a Renderer with the position, size and flags specified.
     *  \param title Title of the Window.
     *  \param x X coordinates of the initial position of the window.
     *  \param y Y coordinates of the initial position of the window..
     *  \param width Width of the Window.
     *  \param height Height of the Window.
     *  \param window_flags Flags for the Window creation. Default no flags.
     *  \param rederer_flags Flags for the Renderer creation. Default no flags.
     */
    Window(const char* title, int x, int y, int width, int height, Uint32 window_flags = 0, Uint32 rederer_flags = 0);

    /** \brief Free resources and destroy the Renderer and the Window.
     */
    ~Window();

    void operator=(const Window&) = delete;  //!< Does not make sense to "copy" a Window.

    /** \brief Clear the Renderer with the background color.
     *
     *  \sa setBackgroundColor()
     */
    inline void clear();

    /** \brief Set the background color.
     *
     *  \param red Red component of the color.
     *  \param green Green component of the color.
     *  \param blue Blue component of the color.
     *  \param alpha Alpha component of the color.
     *
     *  \sa clear()
     */
    inline void setBackgroundColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

    /** \brief Draw the portion of the texture specified by srcrect in the portion of the window specified by dstrect.
     *
     *  \param texID Id of the texture.
     *  \param srcrect Portion of the texture to be drawn.
     *  \param dstrect Portion of the window where the texture is going to be drawn.
     */
    void render(unsigned texID,const SDL_Rect* srcrect,const SDL_Rect* dstrect);

    /** \brief Draw the portion of the texture specified by srcrect in the portion of the window specified by dstrect.
     *
     *  This version can add some transformation to the drawing. Can rotate and flip the texture.
     *
     *  \param texID Id of the texture.
     *  \param srcrect Portion of the texture to be drawn.
     *  \param dstrect Portion of the window where the texture is going to be drawn.
     *  \param angle Angle to rotate the texture.
     *  \param center A SDL_Point pointer that represents the center of rotation of the texture. if null, the center of dstrect will be used.
     *  \param flip A SDL_RendererFlip with be values SDL_FLIP_NONE (do not flip), SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL or diagonal flip (both horizontal and vertical), use bitwise or ('|' operator).
     */
    void render(unsigned texID,const SDL_Rect* srcrect,const SDL_Rect* dstrect,const double angle,const SDL_Point* center,const SDL_RendererFlip flip);

    /** \brief Update the window. Similar to swapbuffers in a double buffer rendering.
     */
    void present() {SDL_RenderPresent(renderer);}

    /** \brief Load an image to create a texture in this renderer.
     *
     *  \param url Image file to be loaded.
     *  \return An id to the texture loaded. Use this id to render the texture or to change the image associated with the texture.
     *  \sa reloadImg(), render()
     */
    unsigned loadImg(const char *url);

    /** \brief Reload an image to an already created texture.
     *
     *  \param url Image file to be reloaded.
     *  \param An id to the texture already created.
     *  \sa loadImg(), render()
     */
    unsigned reloadImg(const char *url, unsigned id);

  private:
    zbe::SDL_Starter &sdl;                   //!< SDL instance.
    SDL_Window* window;                       //!< Window.
    SDL_Renderer* renderer;                   //!< Renderer associated with the window
    unsigned ntextures;                       //!< Number of texture loaded.
    std::vector<SDL_Texture*> imgCollection;  //!< Collection of texture loaded.
    std::mutex m;                             //!< Mutex to avoid race conditions.
};

}  // namespace zbe

#endif  // SRC_SDL_WINDOW_H_
