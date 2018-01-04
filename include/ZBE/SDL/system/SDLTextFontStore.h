/**
 * Copyright 2010 Batis Degryll Ludo
 * @file SDLTextFontStore.h
 *
 * @since 2017/06/11
 * @date 2017/06/11
 * @author Ludo
 * @brief Structure for load and store TTF fonts using SDL.
 */

#ifndef ZBE_SDL_SYSTEM_SDLFONTSTORE_H_
#define ZBE_SDL_SYSTEM_SDLFONTSTORE_H_


#include <vector>
#include <mutex>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ZBE/core/system/SysError.h"

#include "ZBE/SDL/system/SDLImageStore.h"

namespace zbe {

struct ZBE_Font {
  TTF_Font* font;
  SDL_Color color;
};

class SDLTextFontStore {

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

} //namespace zbe

#endif  // ZBE_SDL_SYSTEM_SDLFONTSTORE_H_
