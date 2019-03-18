/**
* Copyright 2015 Batis Degryll Ludo
* @file SDLImgLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief SDL implementation of ImgLoader.
* of the loaded image.
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#ifndef ZBE_SDL_RESOURCES_LOADERS_SDLIMGLOADER_H_
#define ZBE_SDL_RESOURCES_LOADERS_SDLIMGLOADER_H_

#include <filesystem>
#include <memory>

#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/ImgDefLoader.h"

#include "ZBE/SDL/system/SDLWindow.h"

namespace zbe {

/** \brief SDL implementation of ImgLoader.
*/
class ZBEAPI SDLImgLoader : public RsrcLoader {
public:

 /** \brief Builds an SDLImgLoader from a SDLImageStore and the file extension supported (PNG by default)
  *  \imgStore SDLImgLoader to use.
  *  \extension Extension supported. PNG by default.
  */
 SDLImgLoader(std::shared_ptr<zbe::SDLImageStore> imgStore, std::shared_ptr<ImgDefLoader> imgDefLoader, std::filesystem::path extension = ".png")
   : imgStore(imgStore), imgDefLoader(imgDefLoader), ext(extension) {}

 /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
 void load(std::filesystem::path filePath) {
    uint64_t imgId = imgStore->loadImg(filePath.c_str());  // TODO test with ut8
    if(imgId > 0) {
      std::filesystem::path defFilePath = generateDefPath(filePath);
      imgDefLoader->loadImgDef(defFilePath, imgId);
    }
 }

 /** \brief Tells if a file extension is loadable.
  *  \param extension Image file extension.
  *  \return True if the extensions is loadable.
  */
 bool isLoadable(std::filesystem::path extension) {
   return (ext.compare(extension) == 0);
 }

private:

 std::filesystem::path generateDefPath(const std::filesystem::path& p) {
   std::filesystem::path ext = imgDefLoader->getExtension();
   std::filesystem::path out = p;
   return (out.replace_extension(ext));
 }

 std::shared_ptr<zbe::SDLImageStore> imgStore;
 std::shared_ptr<ImgDefLoader> imgDefLoader;
 std::filesystem::path ext;

};

}  // namespace zbe

#endif  // ZBE_SDL_RESOURCES_LOADERS_SDLIMGLOADER_H_
