/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONMultiSpriteSheetLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief JSON loader for MultiSpriteSheet's
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONMULTISPRITESHEETLOADER_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONMULTISPRITESHEETLOADER_H_

#include <filesystem>
#include <fstream>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"

#include "ZBE/factories/Factory.h"
#include "ZBE/resources/loaders/RsrcLoader.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief SDL implementation of ImgLoader.
*/
class JSONMultiSpriteSheetLoader : public RsrcLoader {
public:

  /** \brief Load an image
  *  \param filePath Path to image file.
  *  \return An id to the image loaded.
  */
  void load(std::filesystem::path filePath) override {
    std::ifstream ifs(filePath);
    JSONGraphicsLoaders::JSONMultiSpriteSheetFileLoad(ifs, spriteSheetRsrc, nrd, rsrcImgDef);
  }

  /** \brief Tells if a file extension is loadable.
  *  \param extension Image file extension.
  *  \return True if the extensions is loadable.
  */
  bool isLoadable(std::filesystem::path extension) override {
    static const std::filesystem::path ext(".json");
    return (ext.compare(extension) == 0);
  }

  void setSpriteSheetRsrc(RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >* ssr) {
    this->spriteSheetRsrc = ssr;
  }
  void setNameRsrcDictionary(NameRsrcDictionary* nameRsrcDict) {
    this->nrd = nameRsrcDict;
  }
  void setRsrcModelSheet(RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >* rms) {
    this->rsrcModelSheet = rms;
  }
  void setRsrcImgDef(RsrcStore<ImgDef>* rid) {
    this->rsrcImgDef = rid;
  }
private:
  RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >* spriteSheetRsrc = nullptr;
  NameRsrcDictionary* nrd = nullptr;
  RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >* rsrcModelSheet = nullptr;
  RsrcStore<ImgDef>* rsrcImgDef = nullptr;
};


/** \brief Factory for JSONMultiSpriteSheetLoader.
*/
class JSONMultiSpriteSheetLoaderFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<JSONMultiSpriteSheetLoader> jsonLoader = std::make_shared<JSONMultiSpriteSheetLoader>();
    rsrcLoaderRsrc.insert("RsrcLoader."s + name, jsonLoader);
    jsonMultiSpriteSheetLoaderRsrc.insert("JSONMultiSpriteSheetLoader."s + name, jsonLoader);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto jsonLoader = jsonMultiSpriteSheetLoaderRsrc.get("JSONMultiSpriteSheetLoader."s + name);
      jsonLoader->setSpriteSheetRsrc(&RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >::getInstance());
      jsonLoader->setNameRsrcDictionary(&NameRsrcDictionary::getInstance());
      jsonLoader->setRsrcModelSheet(&RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >::getInstance());
      jsonLoader->setRsrcImgDef(&RsrcStore<ImgDef>::getInstance());
    } else {
        SysError::setError("JSONMultiSpriteSheetLoaderFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<RsrcLoader>& rsrcLoaderRsrc = RsrcStore<RsrcLoader>::getInstance();
  RsrcStore<JSONMultiSpriteSheetLoader>& jsonMultiSpriteSheetLoaderRsrc = RsrcStore<JSONMultiSpriteSheetLoader>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONMULTISPRITESHEETLOADER_H_
