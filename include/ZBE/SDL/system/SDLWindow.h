/**
 * Copyright 2010 Batis Degryll Ludo
 * @file SDL_Window.h
 *
 * @since 2015/05/30
 * @date 2018/02/25
 * @author Degryll Ludo
 * @brief  Three structures:
 *  - SDLWindow: Create a windows using SDL 2.0.
 *  - SDLImageStore: Structure for load and store images using SDL.
 *  - SDLTextFontStore: Structure for load and store TTF fonts using SDL.
 */

#ifndef ZBE_SDL_SYSTEM_SDLWINDOW_H_
#define ZBE_SDL_SYSTEM_SDLWINDOW_H_

#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ZBE/core/system/SysError.h"

#include "ZBE/SDL/starters/SDL_Starter.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI SDLTextFontStore;
class ZBEAPI SDLImageStore;

/**
 * @class ZBEAPI SDLWindow
 * @brief Used to create windows using SDL 2.0.
 */
class ZBEAPI SDLWindow {
public:
  SDLWindow(const SDLWindow&) = delete;  //!< Does not make sense to "copy" a SDLWindow.
  void operator=(const SDLWindow&) = delete;  //!< Does not make sense to "copy" a SDLWindow.

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

  /** \brief internal SDLImageStore getter
   */
  std::shared_ptr<SDLImageStore> getImgStore() {return (imgStore);}

  /** \brief internal SDLTextFontStore getter
   */
  std::shared_ptr<SDLTextFontStore> getFontStore() {return (fontStore);}

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
      SysError::setError(std::string("ERROR: SDL could not set the background color! SDL ERROR: ") + SDL_GetError());
    }
  }

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

  /** \brief Update the SDLWindow. Similar to swapbuffers in a double buffer rendering.
   */
  void present() {SDL_RenderPresent(renderer);}

  /** \brief issue #25
   */
  void render2Texture() {
    SDL_SetRenderTarget(renderer, output);
  }

  /** \brief issue #25
   */
  void render2Screen() {
    SDL_SetRenderTarget(renderer, nullptr);
  }

  /** \brief issue #25
   */
  void readPixels(char* data, int pitch) {
    SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_BGR888, data, pitch);
  }

protected:
  /** \brief Returns internal SDL_Window.
   *  \return internal SDL_Window.
   */
  SDL_Window* getSDL_Window() {
    return window;
  }

private:
  SDL_Starter &sdl;                            //!< SDL instance.
  SDL_Window* window;                          //!< Window.
  SDL_Renderer* renderer;                      //!< Renderer associated with the window
  SDL_Texture* output;                         //!< Output texture.
  std::shared_ptr<SDLImageStore> imgStore;     //!< Store for images.
  std::shared_ptr<SDLTextFontStore> fontStore; //!< Store for text fonts.
};

/**
 * @class ZBEAPI SDLImageStore
 * @brief Structure for load and store images using SDL.
 */
class ZBEAPI SDLImageStore {
public:
    SDLImageStore(const SDLImageStore&) = delete; //!< Delete copy constructor
    void operator=(const SDLImageStore&) = delete; //!< Delete assing aperator

    /** \brief Creates a new SDLImageStore associated to a renderer.
     *  \param renderer SDL_Renderer to use.
     */
    SDLImageStore(SDL_Renderer* renderer);

    /** \brief Default destructor. Will free all loaded textures.
     */
    virtual ~SDLImageStore();

    /** \brief Store a texture.
     *
     *  \param texture Texture to be stored.
     *  \return An id to the texture loaded. Use this id to render the texture or to change the image associated with the texture.
     *  \sa reloadImg(), loadImg()
     */
    uint64_t storeTexture(SDL_Texture * texture);

    /** \brief Load an image to create a texture in this store.
     *
     *  \param url Image file to be loaded.
     *  \return An id to the texture loaded. Use this id to render the texture or to change the image associated with the texture.
     *  \sa reloadImg(), storeTexture()
     */
    uint64_t loadImg(const char *url);

    /** \brief Load an image from an array to create a texture in this store.
     *
     *  \param data Pixel data in bytes.
     *  \param width Width of the image.
     *  \param height Height of the image.
     *  \param depth Depth of color bits.
     *  \param pitch Rows in bytes of the image.
     *  \return An id to the texture loaded. Use this id to render the texture or to change the image associated with the texture.
     *  \sa reloadImg(), storeTexture()
     */
    uint64_t loadImg(const char *data, int width, int height, int depth, int pitch);

    /** \brief Reload an image to an already created texture.
     *
     *  \param url Image file to be reloaded.
     *  \param An id to the texture already created.
     *  \sa loadImg(), storeTexture()
     */
    uint64_t reloadImg(const char *url, uint64_t id);

    /** \brief Return a stored texture;
     *  \param An id to the texture already created.
     *  \return a texture.
     *  \sa loadImg(), storeTexture()
     */
    SDL_Texture* getTexture(uint64_t id);

private:

    uint64_t ntextures;                       //!< Number of loaded textures.
    std::vector<SDL_Texture*> imgCollection;  //!< Collection of textures.
    std::mutex m;                             //!< Mutex to avoid race conditions.
    //std::mutex mf;                            //!< Another mutex to avoid race conditions.
    SDL_Renderer* renderer;

};

struct ZBE_Font {
  TTF_Font* font;
  SDL_Color color;
};

/**
 * @class ZBEAPI SDLFontStore
 * @brief Structure for load and store TTF fonts using SDL.
 */
class ZBEAPI SDLTextFontStore {
public:

    SDLTextFontStore(const SDLTextFontStore&) = delete; //!< Delete copy constructor
    void operator=(const SDLTextFontStore&) = delete; //!< Delete assing aperator

    /** \brief Creates a new SDLTextFontStore associated to a renderer.
     *  \param renderer SDL_Renderer to use.
     */
    SDLTextFontStore(std::shared_ptr<SDLImageStore> imageStore, SDL_Renderer* renderer);

    /** \brief Adds a font to the font collection.
     *
     *  \param font Font type file.
     *  \param size Font size.
     *  \param Font Color.
     *  \return An id to the font loaded.
     *  \sa loadImg(), render()
     */
    uint64_t loadFont(const char *fontName, int size, SDL_Color color);

    /** \brief Load a text with a font and a color to create a texture in this renderer.
     *
     *  \param url Image file to be loaded.
     *  \return An id to the texture loaded. Use this id to render the texture or to change the image associated with the texture.
     *  \sa loadImg(), render()
     */
    uint64_t loadText(char *text, TTF_Font *font, SDL_Color color);

    /** \brief Creates a texture from a text and a font.
     *  \param fontID The ID of the font.
     *  \param text The text.
     *  \return the generated texture.
     */
    SDL_Texture* renderText(uint64_t fontID, const char *text);

private:

    uint64_t nfonts;                          //!< Number of loaded fonts.
    std::vector<ZBE_Font> fontCollection;     //!< Collection of fonts.
    std::mutex m;                             //!< Mutex to avoid race conditions.
    std::mutex mf;                            //!< Another mutex to avoid race conditions.
    std::shared_ptr<SDLImageStore> imageStore; //!< ImageStore to store pre-rendered texts.
    SDL_Renderer* renderer;                   //!< Renderer to be used for drawing.

};

}  // namespace zbe

#endif  // ZBE_SDL_SYSTEM_SDLWINDOW_H_
