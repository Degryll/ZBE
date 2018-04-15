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
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "ZBE/graphics/MultiSpriteSheet.h"

namespace zbe {

using json = nlohmann::json;

ImgDef JSONImgDefLoad(json j, uint64_t graphicsId);

std::unordered_map<std::string, ImgDef> JSONImgDefFileLoad(std::istream& is, uint64_t graphicsId);


}  // namespace zbe

#endif  // ZBE_JSON_GRAPHICS_JSONGRAPHICSLOADERS_H_
