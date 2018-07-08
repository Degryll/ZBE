/**
 * Copyright 2015 Batis Degryll Ludo
 * @file JSONGraphicsLoaders.cpp
 * @since 2018-04-12
 * @date 2018-04-12
 * @author Batis Degryll Ludo
 * @brief Functions to load image properties from json files.
 */

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/graphics/SpriteSheet.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/resources/contextnames.h"

namespace zbe {

using json = nlohmann::json;

ImgDef JSONImgDefLoad(json j, uint64_t graphicsId) {
  try {
    uint64_t frameTime = j["frameTime"];
    unsigned frameAmount = j["frameAmount"];
    Region2D region({j["region"][0],j["region"][1]},{j["region"][2],j["region"][3]});
    Vector2D regionOffset({j["regionOffset"][0],j["regionOffset"][1]});
    return ImgDef(graphicsId, frameTime, frameAmount, region, regionOffset);
  } catch(nlohmann::detail::type_error &e) {
    SysError::setError(std::string("ERROR: Json failed to load ImgDef for id ") +  std::to_string(graphicsId) + std::string(" because: ") + std::string(e.what()));
    return ImgDef(graphicsId);
  }
}

void JSONImgDefFileLoad(std::istream& is, uint64_t graphicsId) {

  RsrcStore<ImgDef>& rsrc = RsrcStore<ImgDef>::getInstance();
  NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();

  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json imgDefs = j["imgdefs"];
    for (auto imgNode : imgDefs) {
      std::string nodeName = imgNode["name"];
      ImgDef imgDef = JSONImgDefLoad(imgNode, graphicsId);
      uint64_t id = SysIdGenerator::getId();
      rsrc.insert(id, std::make_shared<ImgDef>(imgDef));
      nrd.insert(cn::IMGDEF + cn::SEPARATOR + name + cn::SEPARATOR + nodeName, id);
    }
  } catch (json::parse_error &e) {
    SysError::setError(std::string("ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("ERROR: Json failed to load ImgDef for id ") + std::to_string(graphicsId) + std::string(" because: ") + std::string(e.what()));
  }

}

SprtDef JSONSprtDefLoad(json j) {
  try {
    RsrcStore<ImgDef>& rsrc = RsrcStore<ImgDef>::getInstance();
    NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();
    std::string imgName = j["img"];
    uint64_t imgDefId = nrd.get(cn::IMGDEF + cn::SEPARATOR + imgName);
    if(imgDefId > 0){
      std::shared_ptr<ImgDef> storedImgDef = rsrc.get(imgDefId);
      ImgDef imgDef(*storedImgDef);
      Vector2D drawOffset({j["drawOffset"][0],j["drawOffset"][1]});
      Vector2D scale({j["scale"][0],j["scale"][1]});
      return SprtDef(imgDef, drawOffset, scale);
    } else{
      SysError::setError(std::string("ERROR: Json failed to build MultiSpriteSheet. Referenced ImgDef (") + imgName + std::string(") has id zero."));
    }
  } catch(nlohmann::detail::type_error &e) {
    SysError::setError(std::string("ERROR: Json failed to load MultiSpriteSheet because: ") + std::string(e.what()));
  }
  return SprtDef();  // TODO create default ImgDef & image.
}

void JSONMultiSpriteSheetFileLoad(std::istream& is) {
  NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();
  RsrcStore<zbe::SpriteSheet<zbe::AnimatedSprite> >& rsrc = RsrcStore<zbe::SpriteSheet<zbe::AnimatedSprite> >::getInstance();

  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json imgDefs = j["sprtdefs"];
    std::shared_ptr<MultiSpriteSheet> sprtSheet = std::make_shared<MultiSpriteSheet>(j.size());
    for (auto sprtNode : imgDefs) {
      std::string stateName = sprtNode["name"];
      SprtDef sprtDef = JSONSprtDefLoad(sprtNode);
      sprtSheet->setSprite(nrd.get(cn::STATE + cn::SEPARATOR + stateName), sprtDef);
      if (!sprtNode["default"].is_null() && sprtNode["default"]) {
        sprtSheet->setDefaultSprite(sprtDef);
      }
    }
    uint64_t id = SysIdGenerator::getId();
    rsrc.insert(id, sprtSheet);
    nrd.insert(cn::SPRTSHEET + cn::SEPARATOR + name, id);
  } catch (json::parse_error &e) {
    SysError::setError(std::string("ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("ERROR: Json failed to load MultiSpriteSheet because: ") + std::string(e.what()));
  }
}

}  // namespace zbe
