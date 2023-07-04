/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONSpriteOGLModelSheetLoader.h
* @since 2020-09-03
* @date 2020-09-03
* @author Batis Degryll Ludo
* @brief JSON loader for SimpleModelOGLModelSheet's
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONSPRITEOGLMODELSHEETLOADER_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONSPRITEOGLMODELSHEETLOADER_H_

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"
#include "ZBE/SDL/OGL/SDLOGLWindow.h"
#include "ZBE/resources/loaders/RsrcLoader.h"
#include "ZBE/resources/definitions.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief JSON loader for SimpleModelOGLModelSheet's
*/
class ZBEAPI JSONSpriteOGLModelSheetLoader : public RsrcLoader {
public:

 /** \brief Empty constructir. Creted object needs to be setup
  */
//JSONSpriteOGLModelSheetLoader() = default;
 /* \brief It sets up the window to be used.
 */
 void setWindow(std::shared_ptr<SDLOGLWindow> window) {
   this->window = window;
 }

 /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
 void load(std::filesystem::path filePath);

 /** \brief Tells if a file extension is loadable.
  *  \param extension Image file extension.
  *  \return True if the extensions is loadable.
  */
 bool isLoadable(std::filesystem::path extension) {
   static const std::filesystem::path ext(".json");
   return (ext.compare(extension) == 0);
 }

private:
  std::shared_ptr<SDLOGLWindow> window = nullptr;
  RsrcStore<OGLModelSheet<uint64_t, Vector2D, Vector2D>> &rsrcModelSheet = RsrcStore<OGLModelSheet<uint64_t, Vector2D, Vector2D>>::getInstance();
  RsrcStore<ImgDef> &rsrcImgDef = RsrcStore<ImgDef>::getInstance();
  NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();
};

class JSONSpriteOGLModelSheetLoaderFtry : virtual public Factory {
public:

  /** \brief Builds a JSONSpriteOGLModelSheetLoader.
   *  \param name Name for the created JSONSpriteOGLModelSheetLoader.
   *  \param cfgId JSONSpriteOGLModelSheetLoader's configuration id.
   */
  void create(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    auto jsoglmsl = std::make_shared<JSONSpriteOGLModelSheetLoader>();
    rsrclRsrc.insert("RsrcLoader."s + name, jsoglmsl);
    jsoglmslRsrc.insert("JSONSpriteOGLModelSheetLoader."s + name, jsoglmsl);
  }

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId){
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;
      json window = j["window"];
      if(!window.is_string()) {
        SysError::setError("Bad config for JSONSpriteOGLModelSheetLoaderFtry - window."s + window.get<std::string>());
        return;
      }

      auto winname = j["window"].get<std::string>();
      auto win = sdlOGLWindowRsrc.get("SDLOGLWindow."s + winname);

      auto jsoglmsl = jsoglmslRsrc.get("JSONSpriteOGLModelSheetLoader."s + name);
      jsoglmsl->setWindow(win);
    } else {
      SysError::setError("JSONSpriteOGLModelSheetLoaderFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<SDLOGLWindow> &sdlOGLWindowRsrc = RsrcStore<SDLOGLWindow>::getInstance();
  RsrcStore<JSONSpriteOGLModelSheetLoader> &jsoglmslRsrc = RsrcStore<JSONSpriteOGLModelSheetLoader>::getInstance();
  RsrcStore<RsrcLoader> &rsrclRsrc = RsrcStore<RsrcLoader>::getInstance();

};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONSPRITEOGLMODELSHEETLOADER_H_
