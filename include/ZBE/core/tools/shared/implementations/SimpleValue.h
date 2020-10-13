/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SimpleValue.h
 * @since 2017-06-28
 * @date 2017-06-28
 * @author Batis Degryll Ludo
 * @brief Stores a value that can be modified.
 */

#ifndef ZBE_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_
#define ZBE_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_

#include <string>
#include <nlohmann/json.hpp>

#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/system/system.h"

#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"
#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/factories/Factory.h"

namespace zbe {

/** Stores a value that can be modified.
 */
template <typename T>
class SimpleValue : public Value<T> {
public:
  /** brief Void constructor.
   */
  SimpleValue() : v() {}

  /** brief Parametrized contructor.
   *  param value Value to store.
   */
  SimpleValue(T value) : v(value) {}

  /** brief Sets the value.
   *  param value Value to store.
   */
  void set(T value) {
    v = value ;
  }

  /** brief Returns the value.
   *  return value;
   */
  T& get() {
    return v;
  }

// TODO no funciona con vector
//  /** brief Modifies stored value by the param received.
//   *  param value Value to add.
//   */
//  void add(T value) {
//    v += value;
//  }

private:
  T v;
};

class ZBEAPI SimpleValueFtry : public Factory {
public:
  /** \brief Builds a SimpleValue.
   *  \param name Name for the created SimpleValue.
   *  \param cfgId SimpleValue's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

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
         ||(std::is_same<T, std::string>::value && value.at(0).is_string()))){
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

  template <typename T>
  inline void parse(std::string name, nlohmann::json cfg, RsrcStore<Value<T> > &valueRsrc, RsrcDictionary<T> &literalStore) {
    using namespace std::string_literals;
    for (auto item : cfg.items()) {
      //--
      auto val = valueRsrc.get(name + "."s + item.key());
      val->set(parseSingleValue(item.value(), literalStore));
      //---
      // por si generalizamos
      // if (item.value().is_array() && item.value().size() > 1){
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
      auto c = 0;
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
      auto c = 0;
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

#endif  // ZBE_CORE_TOOLS_SHARED_IMPLEMENTATIONS_SIMPLEVALUE_H_
