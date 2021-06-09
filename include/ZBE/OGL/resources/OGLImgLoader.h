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

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

namespace zbe {

/** \brief OGL implementation of ImgLoader.
*/
class OGLImgLoader : public RsrcLoader {
public:

 /** \brief Empty constructor, extension is ".png" by default.
  *  \extension Extension supported. PNG by default.
  */
 OGLImgLoader() : texStore(nullptr), imgDefLoader(nullptr), ext(".png") {}

 /** \brief Builds an OGLImgLoader from a OGLTextureStore and the file extension supported (PNG by default)
  *  \texStore OGLImgLoader to use.
  *  \extension Extension supported. PNG by default.
  */
 OGLImgLoader(zbe::OGLTextureStore* texStore, std::shared_ptr<RsrcDefLoader> imgDefLoader, std::filesystem::path extension = ".png")
    : texStore(texStore), imgDefLoader(imgDefLoader), ext(extension) {}

 /** \brief Sets the image store.
  *  \param texStore The image store.
  */
 void setTexStore(OGLTextureStore* texStore) {
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

  zbe::OGLTextureStore* texStore;
  std::shared_ptr<RsrcDefLoader> imgDefLoader;
  std::filesystem::path ext;
};

/** \brief Factory for OGLImgLoader.
 */
class OGLImgLoaderFtry : virtual public Factory {
public:

  /** \brief Builds a OGLImgLoader.
   *  \param name Name for the created OGLImgLoader.
   *  \param cfgId OGLImgLoader's configuration id.
   */
   void create(std::string name, uint64_t) {
     using namespace std::string_literals;

     auto loader = std::make_shared<OGLImgLoader>();
     sdlImgLoaderRsrc.insert("OGLImgLoader."s + name, loader);
     rsrcLoaderRsrc.insert("RsrcLoader."s + name, loader);
   }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
   void setup(std::string name, uint64_t cfgId) {
     using namespace std::string_literals;
     using namespace nlohmann;
     std::shared_ptr<json> cfg = configRsrc.get(cfgId);

     if(cfg) {
       auto j = *cfg;
       json windowname = j["window"];
       json imgdefname = j["imgdef"];
       json extension = j["extension"];

       if(!windowname.is_string()) {
         SysError::setError("Bad config for OGLImgLoaderFtry - window."s + windowname.get<std::string>());
         return;
       }

       if(!imgdefname.is_string()) {
         SysError::setError("Bad config for OGLImgLoaderFtry - imgdef."s + imgdefname.get<std::string>());
         return;
       }

       auto loader = sdlImgLoaderRsrc.get("OGLImgLoader."s + name);
       auto sdlwin = sdloglWindowRsrc.get("SDLOGLWindow."s + windowname.get<std::string>());
       auto defLoader = rsrcDefLoaderRsrc.get("RsrcDefLoader."s + imgdefname.get<std::string>());

       loader->setTexStore(sdlwin->getTextureStore());
       loader->setImgDefLoader(defLoader);

       if(extension.is_string()) {
         loader->setExtension(extension.get<std::string>());
       }

     } else {
       SysError::setError("OGLImgLoaderFtry config for "s + name + " not found."s);
     }
   }

private:
  //NameRsrcDictionary &dict = NameRsrcDictionary::getInstance();
  RsrcDictionary<std::string>& strStore = RsrcDictionary<std::string>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<OGLImgLoader> &sdlImgLoaderRsrc = RsrcStore<OGLImgLoader>::getInstance();
  RsrcStore<RsrcLoader> &rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();
  RsrcStore<RsrcDefLoader> &rsrcDefLoaderRsrc = RsrcStore<RsrcDefLoader>::getInstance();
  RsrcStore<SDLOGLWindow> &sdloglWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_OGL_RESOURCES_OGLIMGLOADER_H_
