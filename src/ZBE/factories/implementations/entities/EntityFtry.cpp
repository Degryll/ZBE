/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EntityFtry.cpp
 * @since 2020-04-09
 * @date 2020-04-09
 * @author Ludo Degryll Batis
 * @brief Factory for Entities.
 */

#include "ZBE/factories/implementations/entities/EntityFtry.h"

namespace zbe {

void EntityFtry::create(std::string name, uint64_t) {
  using namespace std::string_literals;

  std::shared_ptr<Entity> e = std::make_shared<Entity>();
  entityRsrc.insert("Entity."s + name, e);
}

void EntityFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);
  if(cfg) {
    auto j = *cfg;
    auto e = entityRsrc.get("Entity."s + name);
    if (j.find("double") != j.end())  { parse(j["double"],  valueDRsrc, doubleStore, e); }
    if (j.find("float") != j.end())   { parse(j["float"],   valueFRsrc, floatStore, e); }
    if (j.find("uint") != j.end())    { parse(j["uint"],    valueURsrc, uintStore, e); }
    if (j.find("int") != j.end())     { parse(j["int"],     valueIRsrc, intStore, e); }
    if (j.find("bool") != j.end())    { parse(j["bool"],    valueBRsrc, boolStore, e); }
    if (j.find("V2D") != j.end())     { parseV2D(j["V2D"],              e); }
    if (j.find("V3D") != j.end())     { parseV3D(j["V3D"],              e); }
    if (j.find("String") != j.end())  { parse(j["String"],  valueSRsrc, stringStore, e); }
    if (j.find("VString") != j.end()) { parseVString(j["VString"],      e); }

    if (!j["contextTime"].is_string()) {
      SysError::setError("Entity config for contextTime: must be a literal context time name."s);
      return;
    }

    std::string cTimeName = j["contextTime"].get<std::string>();
    if(!cTimeRsrc.contains("ContextTime."s + cTimeName)) {
      SysError::setError("Entity config for contextTime: is not a context time name."s);
      return;
    }

    auto cTime = cTimeRsrc.get("ContextTime."s + cTimeName);
    e->setContextTime(cTime);

  } else {
    SysError::setError("EntityFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
