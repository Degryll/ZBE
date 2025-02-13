/**
 * Copyright 2012 Batis Degryll Ludo
 * @file EntityFtry.h
 * @since 2020-03-18
 * @date 2020-04-09
 * @author Batis, Degrill, Ludo
 * @brief Factory for Entities
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_ENTITIES_ENTITYFTRY_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_ENTITIES_ENTITYFTRY_H_

#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/SysError.h"

#include "ZBE/core/tools/math/Vector.h"
#include "ZBE/core/tools/shared/Value.h"
#include "ZBE/core/tools/shared/implementations/SimpleValue.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/core/entities/Entity.h"

#include "ZBE/factories/Factory.h"

#include "ZBE/core/system/system.h"


namespace zbe {

/** \brief Factory for Entity.
 */
class ZBEAPI EntityFtry : virtual public Factory {
public:

  /** \brief Builds an Entity.
   *  \param name Name for the Entity.
   *  \param cfgId Entity's configuration id.
   */
  void create(std::string name, uint64_t) override;

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId) override;

private:
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcDictionary<uint64_t>& uintStore = RsrcDictionary<uint64_t>::getInstance();
  RsrcDictionary<double>& doubleStore = RsrcDictionary<double>::getInstance();
  RsrcDictionary<float>& floatStore = RsrcDictionary<float>::getInstance();
  RsrcDictionary<bool>& boolStore = RsrcDictionary<bool>::getInstance();
  RsrcDictionary<std::string>& stringStore = RsrcDictionary<std::string>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();

  RsrcStore<nlohmann::json> &configRsrc = RsrcStore<nlohmann::json>::getInstance();

  RsrcStore<Entity> &entityRsrc = RsrcStore<Entity>::getInstance();
  RsrcStore<Value<double> > &valueDRsrc = RsrcStore<Value<double> >::getInstance();
  RsrcStore<Value<float> > &valueFRsrc = RsrcStore<Value<float> >::getInstance();
  RsrcStore<Value<uint64_t> > &valueURsrc = RsrcStore<Value<uint64_t> >::getInstance();
  RsrcStore<Value<int64_t> > &valueIRsrc = RsrcStore<Value<int64_t> >::getInstance();
  RsrcStore<Value<bool> > &valueBRsrc = RsrcStore<Value<bool> >::getInstance();
  RsrcStore<Value<Vector2D> > &valueV2Rsrc = RsrcStore<Value<Vector2D> >::getInstance();
  RsrcStore<Value<Vector3D> > &valueV3Rsrc = RsrcStore<Value<Vector3D> >::getInstance();
  RsrcStore<Value<std::string> > &valueSRsrc = RsrcStore<Value<std::string> >::getInstance();
  RsrcStore<Value<std::vector<std::string> > > &valueVSRsrc = RsrcStore<Value<std::vector<std::string> > >::getInstance();
  RsrcDictionary<Vector2D> &literalStoreV2D = RsrcDictionary<Vector2D>::getInstance();
  RsrcDictionary<Vector3D> &literalStoreV3D = RsrcDictionary<Vector3D>::getInstance();

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
        SysError::setError("EntityFtry parseArrayElement error: "s + value.get<std::string>() + " has invalid type."s);
        return T();
    }
  }

  template <typename T>
  inline std::shared_ptr<Value<T> > parseSingleValue(nlohmann::json value, RsrcStore<Value<T> > &valueRsrc, RsrcDictionary<T> &literalStore) {
    using namespace std::string_literals;
    if (value.is_string()) {
      return valueRsrc.get(value.get<std::string>());
    } else if(value.is_array() && (value.size() == 1)
         &&(std::is_same_v<T, std::string> == false) && (value.at(0).is_string())) {
      return std::make_shared<SimpleValue<T> >(literalStore.get(value.at(0).get<std::string>()));
    } else if(value.is_array() && (value.size() == 1)
      && ((std::is_floating_point<T>::value && value.at(0).is_number_float())
         ||(std::is_integral<T>::value && value.at(0).is_number_integer())
         ||(std::is_same<T, bool>::value && value.at(0).is_boolean())
         ||(std::is_same<T, std::string>::value && value.at(0).is_string()))) {
      return std::make_shared<SimpleValue<T> >(value.at(0).get<T>());
    } else if((std::is_floating_point<T>::value && value.is_number_float())
         ||(std::is_integral<T>::value && value.is_number_integer())
         ||(std::is_same<T, bool>::value && value.is_boolean())) {
      return std::make_shared<SimpleValue<T> >(value.get<T>());
    } else {
      SysError::setError("EntityFtry parseValue error: "s + value.get<std::string>() + " is invalid."s);
      return (nullptr);
    }
  }

  template <typename T>
  inline void parse(nlohmann::json cfg, RsrcStore<Value<T> > &valueRsrc, RsrcDictionary<T> &literalStore, std::shared_ptr<Entity> e) {
      for (auto item : cfg.items()) {
        auto id = uintStore.get(item.key());
        e->set<T>(id, parseSingleValue(item.value(), valueRsrc, literalStore));
        // por si generalizamos
        // if (item.value().is_array() && item.value().size() > 1) {
        //   e.set<T>(id, parseMultiValue<T, item.value().size()>(item.value(), valueRsrc));
        // } else {
        //   e.set<T>(id, parseSingleValue(item.value(), valueRsrc));
        // }
      }
  }

  inline std::shared_ptr<zbe::Value<Vector3D> > parseV3DValue(nlohmann::json cfg) {
    std::shared_ptr<zbe::Value<Vector3D> > val = std::make_shared<zbe::SimpleValue<Vector3D> >();
    if (cfg.is_string()) {
      val = valueV3Rsrc.get(cfg.get<std::string>());
    } else if(cfg.is_array() && (cfg.size() == 1)
           && (cfg.at(0).is_string())) {
      return std::make_shared<SimpleValue<Vector3D> >(literalStoreV3D.get(cfg.at(0).get<std::string>()));
    } else if (cfg.is_array() && (cfg.size() == 3)) {
      auto c = 0u;
      for (auto item : cfg.items()) {
        val->get()[c++] = parseArrayElement(item.value(), doubleStore);
      }
    }
    return val;
  }

  inline std::shared_ptr<zbe::Value<Vector2D> > parseV2DValue(nlohmann::json cfg) {
    std::shared_ptr<zbe::Value<Vector2D> > val = std::make_shared<zbe::SimpleValue<Vector2D> >();
    if (cfg.is_string()) {
      val = valueV2Rsrc.get(cfg.get<std::string>());
    } else if(cfg.is_array() && (cfg.size() == 1)
           && (cfg.at(0).is_string())) {
      return std::make_shared<SimpleValue<Vector2D> >(literalStoreV2D.get(cfg.at(0).get<std::string>()));
    } else if (cfg.is_array() && (cfg.size() == 2)) {
      auto c = 0u;
      for (auto item : cfg.items()) {
        val->get()[c++] = parseArrayElement(item.value(), doubleStore);
      }
    }
    return val;
  }

  inline std::shared_ptr<zbe::Value<std::vector<std::string> > > parseVStringValue(nlohmann::json cfg) {
    std::shared_ptr<zbe::Value<std::vector<std::string> > > val = std::make_shared<zbe::SimpleValue<std::vector<std::string> > >();
    if (cfg.is_string()) {
      val = valueVSRsrc.get(cfg.get<std::string>());
    } else if (cfg.is_array()) {
      for (auto item : cfg.items()) {
        val->get().emplace_back(parseArrayElement<std::string>(item.value(), stringStore));
      }
    }
    return val;
  }

inline void parseV3D(nlohmann::json cfg, std::shared_ptr<Entity> e) {
    for (auto item : cfg.items()) {
      auto id = uintStore.get(item.key());
      e->set<Vector3D>(id, parseV3DValue(item.value()));
    }
}

inline void parseV2D(nlohmann::json cfg, std::shared_ptr<Entity> e) {
    for (auto item : cfg.items()) {
      auto id = uintStore.get(item.key());
      e->set<Vector2D>(id, parseV2DValue(item.value()));
    }
}

inline void parseVString(nlohmann::json cfg, std::shared_ptr<Entity> e) {
    for (auto item : cfg.items()) {
      auto id = uintStore.get(item.key());
      e->set<std::vector<std::string> >(id, parseVStringValue(item.value()));
    }
}
};

}  // namespace zbe

#endif  // ZBE_FACTORIES_IMPLEMENTATIONS_ENTITIES_ENTITYFTRY_H_
