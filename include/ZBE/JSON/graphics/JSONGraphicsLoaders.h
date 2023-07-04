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
#include "ZBE/resources/definitions.h"

#include "ZBE/core/system/system.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"
#include "ZBE/OGL/graphics/OGLGraphics.h"
#include "ZBE/OGL/graphics/OGLModelSheet.h"
#include "ZBE/OGL/graphics/implementations/OGLModelSheets.h"

namespace zbe {
namespace JSONGraphicsLoaders{

//class ZBEAPI JSONGraphicsLoaders {
//public:
//  using json = nlohmann::json;
//
//  static JSONGraphicsLoaders& getInstance() {
//    static JSONGraphicsLoaders instance;
//    return instance;
//  }

  ZBEAPI ImgDef JSONImgDefLoad(nlohmann::json j, uint64_t graphicsId);

  ZBEAPI void JSONImgDefFileLoad(std::istream& is, uint64_t graphicsId, RsrcStore<ImgDef>& rsrcImgDef, NameRsrcDictionary& nrd);

  ZBEAPI SprtDef JSONSprtDefLoad(nlohmann::json j, RsrcStore<ImgDef>& rsrcImgDef, NameRsrcDictionary& nrd);

  ZBEAPI void JSONMultiSpriteSheetFileLoad(std::istream& is, RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >& rsrcAnimSprt, NameRsrcDictionary& nrd, RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >& rsrcModelSheet, RsrcStore<ImgDef>& rsrcImgDef);

  ZBEAPI void JSONSimpleModelSheetFileLoad(std::istream& is, std::shared_ptr<SDLOGLWindow> window, NameRsrcDictionary& nrd, RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >& rsrcModelSheet, RsrcStore<OGLGraphics> &graphicsStore);

  ZBEAPI void JSONSpriteOGLModelSheetFileLoad(std::istream& is, std::shared_ptr<SDLOGLWindow> window, RsrcStore<OGLModelSheet<uint64_t, Vector2D, Vector2D>>& rsrcModelSheet, NameRsrcDictionary& nrd, RsrcStore<ImgDef>& rsrcImgDef);

  ZBEAPI void JSONLookAtOGLModelSheetFileLoad(std::istream& is, std::shared_ptr<SDLOGLWindow> window, NameRsrcDictionary& nrd, RsrcStore<zbe::OGLModelSheet<uint64_t, double, Vector3D, Vector3D, Vector3D> >& rsrcModelSheet, RsrcStore<OGLGraphics> &graphicsStore);

  ZBEAPI void JSONGLSLProgramFileLoad(std::istream& is, std::shared_ptr<SDLOGLWindow> window, RsrcDictionary<uint64_t>& uintStore);

// private:
//  JSONGraphicsLoaders() {}

//  RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >& rsrcAnimSprt = RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >::getInstance();
//  RsrcStore<ImgDef>& rsrcImgDef = RsrcStore<ImgDef>::getInstance();
//  NameRsrcDictionary& nrd = NameRsrcDictionary::getInstance();
//  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
//  RsrcStore<int>& rsrcModelSheet = RsrcStore<int>::getInstance();
  //RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >& rsrcModelSheet = RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >::getInstance();
//};
}  // namespace JSONGraphicsLoaders
}  // namespace zbe

#endif  // ZBE_JSON_GRAPHICS_JSONGRAPHICSLOADERS_H_
