/**
 * Copyright 2010 Batis Degryll Ludo
 * @file SDLImageStore.h
 *
 * @since 2017/06/11
 * @date 2017/06/11
 * @author Degryll
 * @brief Create a windows using SDL 2.0.
 */

#ifndef ZBE_SDL_SYSTEM_SDLIMAGESTORE_H_
#define ZBE_SDL_SYSTEM_SDLIMAGESTORE_H_


#include <vector>
#include <mutex>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ZBE/core/system/SysError.h"

namespace zbe {

class SDLImageStore {
public:
    SDLImageStore(const SDLImageStore&) = delete; //!< Delete copy constructor
    void operator=(const SDLImageStore&) = delete; //!< Delete assing aperator

    /** \brief Creates a new SDLImageStore associated to a renderer.
     *  \param renderer SDL_Renderer to use.
     */
    SDLImageStore(SDL_Renderer* renderer);

    /** \brief Default destructor. Will free all loaded textures.
     */
    ~SDLImageStore();

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
    std::mutex mf;                            //!< Another mutex to avoid race conditions.
    SDL_Renderer* renderer;

};

} //namespace zbe

#endif  // ZBE_SDL_SYSTEM_SDLIMAGESTORE_H_
