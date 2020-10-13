/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleValueFtry.cpp
 * @since 2020-09-24
 * @date 2020-09-24
 * @author Ludo Degryll Batis
 * @brief Factory for SimpleValue.
 */

#include "ZBE/core/tools/shared/implementations/SimpleValue.h"

namespace zbe {

void SimpleValueFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);
  if(cfg) {
    auto j = *cfg;
    if (j.find("double") != j.end())  { create(name, j["double"],  valueDRsrc); }
    if (j.find("float") != j.end())   { create(name, j["float"],   valueFRsrc); }
    if (j.find("uint") != j.end())    { create(name, j["uint"],    valueURsrc); }
    if (j.find("int") != j.end())     { create(name, j["int"],     valueIRsrc); }
    if (j.find("bool") != j.end())    { create(name, j["bool"],    valueBRsrc); }
    if (j.find("String") != j.end())  { create(name, j["String"],  valueSRsrc); }
    if (j.find("V2D") != j.end())     { create(name, j["V2D"],     valueV2Rsrc);}
    if (j.find("V3D") != j.end())     { create(name, j["V3D"],     valueV3Rsrc);}
    if (j.find("VString") != j.end()) { create(name, j["VString"], valueVSRsrc);}
  } else {
    SysError::setError("SimpleValueFtry config for "s + name + " not found."s);
  }
}

void SimpleValueFtry::setup(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  using namespace nlohmann;
  std::shared_ptr<json> cfg = configRsrc.get(cfgId);
  if(cfg) {
    auto j = *cfg;
    if (j.find("double") != j.end())  { parse(name, j["double"],  valueDRsrc, doubleStore); }
    if (j.find("float") != j.end())   { parse(name, j["float"],   valueFRsrc, floatStore); }
    if (j.find("uint") != j.end())    { parse(name, j["uint"],    valueURsrc, uintStore); }
    if (j.find("int") != j.end())     { parse(name, j["int"],     valueIRsrc, intStore); }
    if (j.find("bool") != j.end())    { parse(name, j["bool"],    valueBRsrc, boolStore); }
    if (j.find("String") != j.end())  { parse(name, j["String"],  valueSRsrc, stringStore); }
    if (j.find("V2D") != j.end())     { parseV2D(name, j["V2D"]); }
    if (j.find("V3D") != j.end())     { parseV3D(name, j["V3D"]); }
    if (j.find("VString") != j.end()) { parseVString(name, j["VString"]); }
  } else {
    SysError::setError("SimpleValueFtry config for "s + name + " not found."s);
  }
}

}  // namespace zbe
