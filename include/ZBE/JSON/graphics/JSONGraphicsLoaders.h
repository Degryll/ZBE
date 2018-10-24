/**
 * Copyright 2015 Batis Degryll Ludo
 * @file JSONGraphicsLoaders.h
 * @since 2018-04-12
 * @date 2018-04-12
 * @author Batis Degryll Ludo
 * @brief Functions to load image properties from json files.
 */

#ifndef ZBE_JSON_GRAPHICS_JSONGRAPHICSLOADERS_H_
#define ZBE_JSON_GRAPHICS_JSONGRAPHICSLOADERS_H_

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/graphics/SpriteSheet.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/system/SysIdGenerator.h"

#include "ZBE/graphics/MultiSpriteSheet.h"
#include "ZBE/resources/contextnames.h"

#include "ZBE/core/system/system.h"

namespace zbe {

class ZBEAPI JSONGraphicsLoaders {
public:
  using json = nlohmann::json;

  static JSONGraphicsLoaders& getInstance() {
    static JSONGraphicsLoaders instance;
    return instance;
  }

  ImgDef JSONImgDefLoad(json j, uint64_t graphicsId);

  void JSONImgDefFileLoad(std::istream& is, uint64_t graphicsId);

  SprtDef JSONSprtDefLoad(json j);

  void JSONMultiSpriteSheetFileLoad(std::istream& is);

private:
  JSONGraphicsLoaders() {}

  RsrcStore<zbe::SpriteSheet<zbe::AnimatedSprite> >& rsrcAnimSprt = RsrcStore<zbe::SpriteSheet<zbe::AnimatedSprite> >::getInstance();
  RsrcStore<ImgDef>& rsrcImgDef = RsrcStore<ImgDef>::getInstance();
  NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();
};

}  // namespace zbe

#endif  // ZBE_JSON_GRAPHICS_JSONGRAPHICSLOADERS_H_
