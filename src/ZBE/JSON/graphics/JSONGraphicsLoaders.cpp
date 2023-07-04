/**
 * Copyright 2015 Batis Degryll Ludo
 * @file JSONGraphicsLoaders.cpp
 * @since 2018-04-12
 * @date 2018-04-12
 * @author Batis Degryll Ludo
 * @brief Functions to load image properties from json files.
 */

#include <cstdio>
#include "ZBE/JSON/graphics/JSONGraphicsLoaders.h"
#include "ZBE/OGL/graphics/implementations/OGLModelSheets.h"

namespace zbe {
namespace JSONGraphicsLoaders {

ImgDef JSONImgDefLoad(nlohmann::json j, uint64_t graphicsId) {
  try {
    uint64_t frameTime = j["frameTime"];
    unsigned frameAmount = j["frameAmount"];
    Region2D region({j["region"][0],j["region"][1]},{j["region"][2],j["region"][3]});
    Vector2D regionOffset({j["regionOffset"][0],j["regionOffset"][1]});
    Region2D texCoord({j["texCoord"][0],j["texCoord"][1]},{j["texCoord"][2],j["texCoord"][3]});
    Vector2D texCoordOffset({j["texCoordOffset"][0],j["texCoordOffset"][1]});
    return ImgDef(graphicsId, frameTime, frameAmount, region, regionOffset, texCoord, texCoordOffset);
  } catch(nlohmann::detail::type_error &e) {
    SysError::setError(std::string("JSONImgDefLoad - ERROR: Json failed to load ImgDef for id ") +  std::to_string(graphicsId) + std::string(" because: ") + std::string(e.what()));
    return ImgDef(graphicsId);
  }
}

void JSONImgDefFileLoad(std::istream& is, uint64_t graphicsId, RsrcStore<ImgDef>& rsrcImgDef, NameRsrcDictionary& nrd) {
  using namespace nlohmann;
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
    SysError::setError(std::string("JSONImgDefFileLoad - ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("JSONImgDefFileLoad - ERROR: Json failed to load ImgDef for id ") + std::to_string(graphicsId) + std::string(" because: ") + std::string(e.what()));
  }

}

SprtDef JSONSprtDefLoad(nlohmann::json j, RsrcStore<ImgDef>& rsrcImgDef, NameRsrcDictionary& nrd) {
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

void JSONSpriteOGLModelSheetFileLoad(std::istream& is, std::shared_ptr<SDLOGLWindow> window, RsrcStore<OGLModelSheet<uint64_t, Vector2D, Vector2D>>& rsrcModelSheet, NameRsrcDictionary& nrd, RsrcStore<ImgDef>& rsrcImgDef) {
  using namespace nlohmann;
  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json sprtDefs = j["sprtdefs"];
    std::shared_ptr<SpriteOGLModelSheet> sprtSheet = std::make_shared<SpriteOGLModelSheet>(window);
    // TODO : De momento solo vamos a soportar un sprite.
    //for (auto sprtNode : sprtDefs) {
    if (sprtDefs.is_array() && sprtDefs.size() >= 1) {
      auto sprtNode = sprtDefs[0];
      std::string stateName = sprtNode["name"];
      SprtDef sprtDef = JSONSprtDefLoad(sprtNode, rsrcImgDef, nrd);
      sprtSheet->setSprite(sprtDef);
      if (sprtDefs.size() > 1) {
        SysError::setError(std::string("ERROR: Invalid number of elements in sprtDefs"));
      }
    } else {
      SysError::setError(std::string("ERROR: sprtDefs is empty"));
    }
    rsrcModelSheet.insert(name, sprtSheet);
    auto gId = nrd.get(name);
  } catch (json::parse_error &e) {
    SysError::setError(std::string("JSONSpriteOGLModelSheetFileLoad - ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("JSONSpriteOGLModelSheetFileLoad - ERROR: Json failed to load MultiSpriteSheet because: ") + std::string(e.what()));
  }
}

void JSONMultiSpriteSheetFileLoad(std::istream& is, RsrcStore<zbe::SpriteSheet<uint64_t, int64_t, double, Vector2D, Vector2D> >& rsrcAnimSprt, NameRsrcDictionary& nrd, RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >& rsrcModelSheet, RsrcStore<ImgDef>& rsrcImgDef) {
  using namespace nlohmann;
  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json sprtDefs = j["sprtdefs"];
    std::shared_ptr<MultiSpriteSheet> sprtSheet = std::make_shared<MultiSpriteSheet>(sprtDefs.size());
    for (auto sprtNode : sprtDefs) {
      std::string stateName = sprtNode["name"];
      SprtDef sprtDef = JSONSprtDefLoad(sprtNode, rsrcImgDef, nrd);
      sprtSheet->setSprite(nrd.get(cn::STATE + cn::SEPARATOR + stateName), sprtDef);
      if (!sprtNode["default"].is_null() && sprtNode["default"]) {
        sprtSheet->setDefaultSprite(sprtDef);
      }
    }
    rsrcAnimSprt.insert(name, sprtSheet);
  } catch (json::parse_error &e) {
    SysError::setError(std::string("JSONMultiSpriteSheetFileLoad - ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("JSONMultiSpriteSheetFileLoad - ERROR: Json failed to load MultiSpriteSheet because: ") + std::string(e.what()));
  }
}

void JSONSimpleModelSheetFileLoad(std::istream& is, std::shared_ptr<SDLOGLWindow> window, NameRsrcDictionary& nrd, RsrcStore<zbe::OGLModelSheet<uint64_t, double, double, Vector3D, Vector3D> >& rsrcModelSheet, RsrcStore<OGLGraphics> &graphicsStore) {
  using namespace std::string_literals;
  using namespace nlohmann;
  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json graphicdefs = j["graphicdefs"];
    json graphicdef =  graphicdefs[0];
    std::string graphicsName = graphicdef["name"];
    std::shared_ptr<SimpleOGLModelSheet> modelSheet = std::make_shared<SimpleOGLModelSheet>(window, "graphics."s + graphicsName, graphicsStore);

    // for (auto graphicdef : graphicdefs) {
    // TODO necesitaremos añadir múltiples definiciones de model a un solo OGLModelSheet en el futuro.
    // }
    rsrcModelSheet.insert(name, modelSheet);
  } catch (json::parse_error &e) {
    SysError::setError(std::string("JSONMultiSpriteSheetFileLoad - ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("JSONMultiSpriteSheetFileLoad - ERROR: Json failed to load SimpleModelSheet because: ") + std::string(e.what()));
  }
}

void JSONLookAtOGLModelSheetFileLoad(std::istream& is, std::shared_ptr<SDLOGLWindow> window, NameRsrcDictionary& nrd, RsrcStore<zbe::OGLModelSheet<uint64_t, double, Vector3D, Vector3D, Vector3D> >& rsrcModelSheet, RsrcStore<OGLGraphics> &graphicsStore) {
  using namespace std::string_literals;
  using namespace nlohmann;
  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json graphicdefs = j["graphicdefs"];
    json graphicdef =  graphicdefs[0];
    std::string graphicsName = graphicdef["name"];
    std::shared_ptr<LookAtOGLModelSheet> modelSheet = std::make_shared<LookAtOGLModelSheet>(window, "graphics."s + graphicsName, graphicsStore);

    // for (auto graphicdef : graphicdefs) {
    // TODO necesitaremos añadir múltiples definiciones de model a un solo OGLModelSheet en el futuro.
    // }
    rsrcModelSheet.insert(name, modelSheet);
  } catch (json::parse_error &e) {
    SysError::setError(std::string("JSONLookAtOGLModelSheetLoad - ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("JSONLookAtOGLModelSheetLoad - ERROR: Json failed to load SimpleModelSheet because: ") + std::string(e.what()));
  }
}

void JSONGLSLProgramFileLoad(std::istream& is, std::shared_ptr<SDLOGLWindow> window, RsrcDictionary<uint64_t>& uintStore) {
  using namespace std::string_literals;
  using namespace nlohmann;
  json j;
  try {
    is >> j;
    std::string name = j["name"];
    json shaderFiles = j["shaderfiles"];
    std::vector<ShaderDef> shaderDefs;
    for (auto fileurl : shaderFiles) {
      std::string fileurlStr = fileurl.get<std::string>();
      std::size_t pos = fileurlStr.rfind(".");
      std::string ext = fileurlStr.substr(pos+1);
      if (ext.compare("vs"s) == 0) {
        shaderDefs.push_back(ShaderDef{fileurlStr, GL_VERTEX_SHADER});
      } else if (ext.compare("fs"s) == 0) {
        shaderDefs.push_back(ShaderDef{fileurlStr, GL_FRAGMENT_SHADER});
      } else if (ext.compare("gs"s) == 0) {
        shaderDefs.push_back(ShaderDef{fileurlStr, GL_GEOMETRY_SHADER});
      }
    }  // for
    auto programid = window->getShaderStore()->loadShader(shaderDefs);
    uintStore.insert(name, programid);

  } catch (json::parse_error &e) {
    SysError::setError(std::string("JSONGLSLProgramFileLoad - ERROR: Json failed to parse: ") + std::string(e.what()));
  } catch (nlohmann::detail::type_error &e) {
    SysError::setError(std::string("JSONGLSLProgramFileLoad - ERROR: Json failed to load SimpleModelSheet because: ") + std::string(e.what()));
  }
}

}  // namespace JSONGraphicsLoaders
}  // namespace zbe
