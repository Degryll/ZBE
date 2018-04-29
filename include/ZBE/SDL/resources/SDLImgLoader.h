/**
 * Copyright 2015 Batis Degryll Ludo
 * @file ImgLoader.h
 * @since 2018-04-19
 * @date 2018-04-19
 * @author Batis Degryll Ludo
 * @brief SDL implementation of ImgLoader.
 * of the loaded image.
 */

#ifndef ZBE_SDL_RESOURCES_LOADERS_SDLIMGLOADER_H_
#define ZBE_SDL_RESOURCES_LOADERS_SDLIMGLOADER_H_

#include <filesystem>
#include <memory>

#include "ZBE/SDL/system/SDLWindow.h"

namespace zbe {

/** \brief SDL implementation of ImgLoader.
 */
class SLDImgLoader {
public:

  /** \brief Builds an SLDImgLoader from a SDLImageStore and the file extension supported (PNG by default)
   *  \imgStore SLDImgLoader to use.
   *  \extension Extension supported. PNG by default.
   */
  SLDImgLoader(std::shared_ptr<zbe::SDLImageStore> imgStore, std::filesystem::path extension = ".png") : imgStore(imgStore), ext(extension) {}

  /** \brief Load an image
   *  \param filePath Path to image file.
   *  \return An id to the image loaded.
   */
  uint64_t loadImg(std::filesystem::path filePath) {
    return imgStore->loadImg(filePath.u8string());
  }

  /** \brief Tells if a file extension is loadable.
   *  \param extension Image file extension.
   *  \return True if the extensions is loadable.
   */
  bool isLoadable(std::filesystem::path extension) {
    return (ext.compare(extension) == 0);
  }

private:
  std::shared_ptr<zbe::SDLImageStore> imgStore;
  std::filesystem::path ext;

};

}  // namespace zbe

#endif  // ZBE_SDL_RESOURCES_LOADERS_SDLIMGLOADER_H_
