/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleValueFtry.h
 * @since 2025-10-16
 * @date 2025-10-16
 * @author Batis Degryll Ludo
 * @brief Factory for SimpleValue.
 */
#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_

#include <string>
#include <nlohmann/json.hpp>
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/containers/RsrcDictionary.h"
#include "ZBE/factories/Factory.h"

namespace zbe {

class SimpleValueFtry : public Factory {
public:
  /** \brief Builds a SimpleValue.
   *  \param name Name for the created SimpleValue.
   *  \param cfgId SimpleValue's configuration id.
   */
  void create(std::string name, uint64_t cfgId) override {
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

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override {
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

private:
  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Value<double> > &valueDRsrc = RsrcStore<Value<double> >::getInstance();
  RsrcStore<Value<float> > &valueFRsrc = RsrcStore<Value<float> >::getInstance();
  RsrcStore<Value<uint64_t> > &valueURsrc = RsrcStore<Value<uint64_t> >::getInstance();
  RsrcStore<Value<int64_t> > &valueIRsrc = RsrcStore<Value<int64_t> >::getInstance();
  RsrcStore<Value<bool> > &valueBRsrc = RsrcStore<Value<bool> >::getInstance();
  RsrcStore<Value<Vector2D> > &valueV2Rsrc = RsrcStore<Value<Vector2D> >::getInstance();
  RsrcStore<Value<Vector3D> > &valueV3Rsrc = RsrcStore<Value<Vector3D> >::getInstance();
  RsrcStore<Value<std::string> > &valueSRsrc = RsrcStore<Value<std::string> >::getInstance();
  RsrcStore<Value<std::vector<std::string> > > &valueVSRsrc = RsrcStore<Value<std::vector<std::string> > >::getInstance();

  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
  RsrcDictionary<double>& doubleStore = RsrcDictionary<double>::getInstance();
  RsrcDictionary<float>& floatStore = RsrcDictionary<float>::getInstance();
  RsrcDictionary<bool>& boolStore = RsrcDictionary<bool>::getInstance();
  RsrcDictionary<std::string>& stringStore = RsrcDictionary<std::string>::getInstance();


  template <typename T>
  inline void create(std::string name, nlohmann::json cfg, RsrcStore<Value<T> > &valueRsrc) {
    using namespace std::string_literals;
      for (auto item : cfg.items()) {
        valueRsrc.insert(name + "."s + item.key(), std::make_shared<SimpleValue<T> >());
      }
  }

DISABLE_WARNING_PUSH(4127) // warning C4127: conditional expression is constant. IS NOT
  template <typename T>
  T parseArrayElement(nlohmann::json value, RsrcDictionary<T> &literalStore) {
    using namespace std::string_literals;
    if (value.is_string()) {
        //auto s = value.get<std::string>();
        //auto sp = valueRsrc.get(s);
        //auto sr = sp->get();
        //return sr;
      return literalStore.get(value.get<std::string>());
    } else if(value.is_array() && (value.size() == 1)
           && ((value.at(0).is_number_float() && std::is_floating_point<T>::value)
              ||(value.at(0).is_number_integer() && std::is_integral<T>::value)
              ||(value.at(0).is_boolean() && std::is_same<T, bool>::value)
              ||(value.at(0).is_string() && std::is_same<T, std::string>::value))) {
      return value.at(0).get<T>();
    } else if((value.is_number_float() && std::is_floating_point<T>::value)
           ||(value.is_number_integer() && std::is_integral<T>::value)
           ||(value.is_boolean() && std::is_same<T, bool>::value)) {
      return value.get<T>();
    } else {
        SysError::setError("SimpleValueFtry parseArrayElement error: "s + value.get<std::string>() + " has invalid type."s);
        return T();
    }
  }

  template <typename T>
  inline T parseSingleValue(nlohmann::json value, RsrcDictionary<T> &literalStore) {
    using namespace std::string_literals;
    if(value.is_array() && (value.size() == 1) && (std::is_same_v<T, std::string> == false) && (value.at(0).is_string())) {
      return literalStore.get(value.at(0).get<std::string>());
    } else if(value.is_array() && (value.size() == 1)
      && ((std::is_floating_point<T>::value && value.at(0).is_number_float())
         ||(std::is_integral<T>::value && value.at(0).is_number_integer())
         ||(std::is_same<T, bool>::value && value.at(0).is_boolean())
         ||(std::is_same<T, std::string>::value && value.at(0).is_string()))) {
      return value.at(0).get<T>();
    } else if((std::is_floating_point<T>::value && value.is_number_float())
         ||(std::is_integral<T>::value && value.is_number_integer())
         ||(std::is_same<T, bool>::value && value.is_boolean())) {
      return value.get<T>();
    } else {
      SysError::setError("SimpleValueFtry parseValue error: "s + value.get<std::string>() + " is invalid."s);
      return T();
    }
  }
DISABLE_WARNING_POP()

  template <typename T>
  inline void parse(std::string name, nlohmann::json cfg, RsrcStore<Value<T> > &valueRsrc, RsrcDictionary<T> &literalStore) {
    using namespace std::string_literals;
    for (auto item : cfg.items()) {
      //--
      auto val = valueRsrc.get(name + "."s + item.key());
      val->set(parseSingleValue(item.value(), literalStore));
      //---
      // por si generalizamos
      // if (item.value().is_array() && item.value().size() > 1) {
      //   e.set<T>(id, parseMultiValue<T, item.value().size()>(item.value(), valueRsrc));
      // } else {
      //   e.set<T>(id, parseSingleValue(item.value(), valueRsrc));
      // }
    }
  }

  inline Vector3D parseV3DValue(nlohmann::json cfg) {
    using namespace std::string_literals;
    Vector3D v3;
    if (cfg.is_array() && (cfg.size() == 3)) {
      auto c = 0u;
      for (auto item : cfg.items()) {
        v3[c++] = parseArrayElement(item.value(), doubleStore);
      }
    } else {
      SysError::setError("SimpleValueFtry parseV3DValue error: Vector3D must be an array with three elements"s);
    }
    return v3;
  }

  inline Vector2D parseV2DValue(nlohmann::json cfg) {
    using namespace std::string_literals;
    Vector2D v2;
    if (cfg.is_array() && (cfg.size() == 2)) {
      auto c = 0u;
      for (auto item : cfg.items()) {
        v2[c++] = parseArrayElement(item.value(), doubleStore);
      }
    } else {
      SysError::setError("SimpleValueFtry parseV2DValue error: Vector2D must be an array with two elements"s);
    }
    return v2;
  }

  inline std::vector<std::string> parseVStringValue(nlohmann::json cfg) {
    std::vector<std::string> vs;
    if (cfg.is_array()) {
      for (auto item : cfg.items()) {
        // TODO quitar este suppress y usar std::transform 
        // cppcheck-suppress useStlAlgorithm
        vs.emplace_back(parseArrayElement<std::string>(item.value(), stringStore));
      }
    }
    return vs;
  }

  inline void parseV3D(std::string name, nlohmann::json cfg) {
    using namespace std::string_literals;
    for (auto item : cfg.items()) {
      auto val = valueV3Rsrc.get(name + "."s + item.key());
      val->set(parseV3DValue(item.value()));
    }
  }

  inline void parseV2D(std::string name, nlohmann::json cfg) {
    using namespace std::string_literals;
    for (auto item : cfg.items()) {
      auto val = valueV2Rsrc.get(name + "."s + item.key());
      val->set(parseV2DValue(item.value()));
    }
  }

  inline void parseVString(std::string name, nlohmann::json cfg) {
    using namespace std::string_literals;
    for (auto item : cfg.items()) {
      auto val = valueVSRsrc.get(name + "."s + item.key());
      val->set(parseVStringValue(item.value()));
    }
  }
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_