/**
 * Copyright 2015 Batis Degryll Ludo
 * @file JSONGraphicsLoaders.cpp
 * @since 2018-04-12
 * @date 2018-04-12
 * @author Batis Degryll Ludo
 * @brief Functions to load image properties from json files.
 */

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"

namespace zbe {

ImgDef JSONGraphicsLoaders::JSONImgDefLoad(json j, uint64_t graphicsId) {
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

void JSONGraphicsLoaders::JSONImgDefFileLoad(std::istream& is, uint64_t graphicsId) {
  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json imgDefs = j["imgdefs"];
    for (auto imgNode : imgDefs) {
      std::string nodeName = imgNode["name"];
      ImgDef imgDef = JSONImgDefLoad(imgNode, graphicsId);
      uint64_t id = SysIdGenerator::getId();
      rsrcImgDef.insert(id, std::make_shared<ImgDef>(imgDef));
      nrd.insert(cn::IMGDEF + cn::SEPARATOR + name + cn::SEPARATOR + nodeName, id);
    }
  } catch (json::parse_error &e) {
    SysError::setError(std::string("ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("ERROR: Json failed to load ImgDef for id ") + std::to_string(graphicsId) + std::string(" because: ") + std::string(e.what()));
  }

}

SprtDef JSONGraphicsLoaders::JSONSprtDefLoad(json j) {
  try {
    std::string imgName = j["img"];
    uint64_t imgDefId = nrd.get(cn::IMGDEF + cn::SEPARATOR + imgName);
    if(imgDefId > 0){
      std::shared_ptr<ImgDef> storedImgDef = rsrcImgDef.get(imgDefId);
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

void JSONGraphicsLoaders::JSONMultiSpriteSheetFileLoad(std::istream& is) {
  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json sprtDefs = j["sprtdefs"];
    std::shared_ptr<MultiSpriteSheet> sprtSheet = std::make_shared<MultiSpriteSheet>(sprtDefs.size());
    for (auto sprtNode : sprtDefs) {
      std::string stateName = sprtNode["name"];
      SprtDef sprtDef = JSONSprtDefLoad(sprtNode);
      sprtSheet->setSprite(nrd.get(cn::STATE + cn::SEPARATOR + stateName), sprtDef);
      if (!sprtNode["default"].is_null() && sprtNode["default"]) {
        sprtSheet->setDefaultSprite(sprtDef);
      }
    }
    uint64_t id = SysIdGenerator::getId();
    rsrcAnimSprt.insert(id, sprtSheet);
    nrd.insert(name, id);
  } catch (json::parse_error &e) {
    SysError::setError(std::string("ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("ERROR: Json failed to load MultiSpriteSheet because: ") + std::string(e.what()));
  }
}

}  // namespace zbe
