/**
 * Copyright 2015 Batis Degryll Ludo
 * @file JSONGraphicsLoaders.cpp
 * @since 2018-04-12
 * @date 2018-04-12
 * @author Batis Degryll Ludo
 * @brief Functions to load image properties from json files.
 */

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"
#include "ZBE/core/system/SysError.h"

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

std::unordered_map<std::string, ImgDef> JSONImgDefFileLoad(std::istream& is, uint64_t graphicsId) {
  std::unordered_map<std::string, ImgDef> m;
  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json imgDefs = j["imgdefs"];
    for (auto imgNode : imgDefs) {
      std::string nodeName = imgNode["name"];
      m[name + "." + nodeName] = JSONImgDefLoad(imgNode, graphicsId);
    }
  } catch (json::parse_error &e) {
    SysError::setError(std::string("ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("ERROR: Json failed to load ImgDef for id ") + std::to_string(graphicsId) + std::string(" because: ") + std::string(e.what()));
  }
  return m;
}

}  // namespace zbe
