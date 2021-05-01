/**
* Copyright 2015 Batis Degryll Ludo
* @file OGLImgLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief OGL implementation of ImgLoader.
* of the loaded image.
* Test on ZBETest/resources/loaders/RsrcLoadTest.cpp
*/

#ifndef ZBE_OGL_RESOURCES_OGLIMGLOADER_H_
#define ZBE_OGL_RESOURCES_OGLIMGLOADER_H_

#include <cstdio>

#include <filesystem>
#include <memory>

#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/loaders/RsrcDefLoader.h"

#include "ZBE/OGL/system/OGLWindow.h"

namespace zbe {

/** \brief OGL implementation of ImgLoader.
*/
class ZBEAPI OGLImgLoader : public RsrcLoader {
public:

 /** \brief Empty constructor, extension is ".png" by default.
  *  \extension Extension supported. PNG by default.
  */
 OGLImgLoader() : texStore(nullptr), imgDefLoader(nullptr), ext(".png") {}

 /** \brief Builds an OGLImgLoader from a OGLTextureStore and the file extension supported (PNG by default)
  *  \texStore OGLImgLoader to use.
  *  \extension Extension supported. PNG by default.
  */
 OGLImgLoader(std::shared_ptr<zbe::OGLTextureStore> texStore, std::shared_ptr<RsrcDefLoader> imgDefLoader, std::filesystem::path extension = ".png")
    : texStore(texStore), imgDefLoader(imgDefLoader), ext(extension) {}

 /** \brief Sets the image store.
  *  \param texStore The image store.
  */
 void settexStore(std::shared_ptr<zbe::OGLTextureStore> texStore) {
   this->texStore = texStore;
 }

 /** \brief Sets the image definition loader
  *  \param imgDefLoader The image definition loader.
  */
 void setImgDefLoader(std::shared_ptr<RsrcDefLoader> imgDefLoader) {
   this->imgDefLoader = imgDefLoader;
 }

 /** \brief Sets the image file extension
  *  \param extension The image file extension.
  */
 void setExtension(std::filesystem::path extension) {
   this->ext = extension;
 }

 /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
 void load(std::filesystem::path filePath) {
    uint64_t imgId = texStore->loadImg(filePath.u8string().c_str());  // TODO test with ut8
    if(imgId > 0) {
      std::filesystem::path defFilePath = generateDefPath(filePath);
      imgDefLoader->loadRsrcDef(defFilePath, imgId);
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

  std::shared_ptr<zbe::OGLTextureStore> texStore;
  std::shared_ptr<RsrcDefLoader> imgDefLoader;
  std::filesystem::path ext;
};

}  // namespace zbe

#endif  // ZBE_OGL_RESOURCES_OGLIMGLOADER_H_
