/**
* Copyright 2015 Batis Degryll Ludo
* @file JSONImgDefLoader.h
* @since 2018-04-19
* @date 2018-04-19
* @author Batis Degryll Ludo
* @brief JSON implementation of a RsrcDefLoader for images.
* Test on ZBETest/resources/loaders/ImgAndDEfloadTest.cpp
*/

#ifndef ZBE_JSON_RESOURCES_LOADERS_JSONIMGDEFLOADER_H_
#define ZBE_JSON_RESOURCES_LOADERS_JSONIMGDEFLOADER_H_

#include <fstream>
#include <filesystem>
#include <iostream>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"

#include "ZBE/resources/loaders/RsrcDefLoader.h"

namespace zbe {

/** \brief JSON implementation of a RsrcDefLoader for images.
 */
class JSONImgDefLoader : public RsrcDefLoader {
public:
  /** \brief Load an image definition
  *  \param url Image definition file to be loaded.
  *  \param imgId Associated image id
  *  \return An id to the image definition.
  */
  void loadRsrcDef(const std::filesystem::path& url, uint64_t imgId) override {
    std::ifstream ifs(url);
    JSONGraphicsLoaders::JSONImgDefFileLoad(ifs, imgId, rsrcImgDef, nrd);
  }

  /** \brief Returns the file extension.
  *  \return The file extension.
  */
  const std::filesystem::path getExtension() override {
    static const std::filesystem::path p(".json");
    return p;
  }

  void setRsrcImgDef(RsrcStore<ImgDef>* rid) {
    this->rsrcImgDef = rid;
  }

  void setNameRsrcDictionary(NameRsrcDictionary* nameRsrcDict) {
    this->nrd = nameRsrcDict;
  }

private:
  RsrcStore<ImgDef>* rsrcImgDef = nullptr;
  NameRsrcDictionary* nrd = nullptr;

};


/** \brief Factory for JSONImgDefLoader.
*/
class JSONImgDefLoaderFtry : public Factory {
public:
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<JSONImgDefLoader> jsonLoader = std::make_shared<JSONImgDefLoader>();

    rsrcDefLoaderRsrc.insert("RsrcDefLoader."s + name, jsonLoader);
    jsonImgDefLoaderRsrc.insert("JSONImgDefLoader."s + name, jsonLoader);
  }

  void setup(std::string name, uint64_t cfgId) override {
    using namespace std::string_literals;
    using namespace nlohmann;
    std::shared_ptr<json> cfg = configRsrc.get(cfgId);

    if(cfg) {
      auto j = *cfg;

      auto jsonLoader = jsonImgDefLoaderRsrc.get("JSONImgDefLoader."s + name);
      jsonLoader->setRsrcImgDef(&RsrcStore<ImgDef>::getInstance());
      jsonLoader->setNameRsrcDictionary(&NameRsrcDictionary::getInstance());
    } else {
        SysError::setError("JSONImgDefLoaderFtry config for "s + name + " not found."s);
    }
  }

private:
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<RsrcDefLoader>& rsrcDefLoaderRsrc = RsrcStore<RsrcDefLoader>::getInstance();
  RsrcStore<JSONImgDefLoader>& jsonImgDefLoaderRsrc = RsrcStore<JSONImgDefLoader>::getInstance();
};
}  // namespace zbe

#endif  // ZBE_JSON_RESOURCES_LOADERS_JSONIMGDEFLOADER_H_
