/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SineOscillator.h
 * @since 2025-10-21
 * @date 2025-10-21
 * @author Degryll Ludo Batis
 * @brief Factories for SineOscillator behaviors.
 */

#ifndef ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_SINEOSCILLATOR_H_
#define ZBE_FACTORIES_IMPLEMENTATIONS_BEHAVIORS_SINEOSCILLATOR_H_

#include <string>
#include <nlohmann/json.hpp>

#include "ZBE/factories/Factory.h"
#include "ZBE/behaviors/SineOscillator.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

namespace zbe {

/** \brief Factory for SineOscillatorF.
 */
class SineOscillatorFFtry : virtual public Factory {
public:
  /** \brief Builds a SineOscillator.
   *  \param name Name for the created SineOscillator.
   *  \param cfgId SineOscillator's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<SineOscillatorF> so(new SineOscillatorF);  // std::make_shared<SineOscillator>();
    behaviorRsrc.insert("Behavior."s + name, so);
    sineOscillatorFRsrc.insert("SineOscillatorF."s + name, so);
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
      if (!j["min"].is_string()) {
        SysError::setError("SineOscillatorFFtry config for min: "s + j["min"].get<std::string>() + ": must be a literal float name."s);
        return;
      }
      if (!j["max"].is_string()) {
        SysError::setError("SineOscillatorFFtry config for max: "s + j["max"].get<std::string>() + ": must be a literal float name."s);
        return;
      }
      if (!j["period"].is_string()) {
        SysError::setError("SineOscillatorFFtry config for period: "s + j["period"].get<std::string>() + ": must be a literal int64_t name."s);
        return;
      }

      std::string minName = j["min"].get<std::string>();
      if(!floatStore.contains(minName)) {
        SysError::setError("SineOscillatorFFtry config for min: "s + minName + " is not a float literal."s);
        return;
      }

      std::string maxName = j["max"].get<std::string>();
      if(!floatStore.contains(maxName)) {
        SysError::setError("SineOscillatorFFtry config for max: "s + maxName + " is not a float literal."s);
        return;
      }

      std::string periodName = j["period"].get<std::string>();
      if(!intStore.contains(periodName)) {
        SysError::setError("SineOscillatorFFtry config for period: "s + periodName + " is not a int64_t literal."s);
        return;
      }

      float min = floatStore.get(minName);
      float max = floatStore.get(maxName);
      int64_t period = intStore.get(periodName);
      auto so = sineOscillatorFRsrc.get("SineOscillatorF."s + name);

      so->setRange(min, max);
      so->setPeriod(period);

    } else {
      SysError::setError("SineOscillatorFFtry config for "s + name + " not found."s);
    }

  }

private:

  RsrcDictionary<float>& floatStore = RsrcDictionary<float>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<float> >& behaviorRsrc = RsrcStore<Behavior<float> >::getInstance();
  RsrcStore<SineOscillatorF>& sineOscillatorFRsrc = RsrcStore<SineOscillatorF>::getInstance();
};

/** \brief Factory for SineOscillatorV3D.
 */
class SineOscillatorV3DFtry : virtual public Factory {
public:
  /** \brief Builds a SineOscillator.
   *  \param name Name for the created SineOscillator.
   *  \param cfgId SineOscillator's configuration id.
   */
  void create(std::string name, uint64_t) override {
    using namespace std::string_literals;
    std::shared_ptr<SineOscillatorV3D> so(new SineOscillatorV3D);  // std::make_shared<SineOscillator>();
    behaviorRsrc.insert("Behavior."s + name, so);
    sineOscillatorFRsrc.insert("SineOscillatorV3D."s + name, so);

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
      if (!j["min"].is_string()) {
        SysError::setError("SineOscillatorV3DFtry config for min: "s + j["min"].get<std::string>() + ": must be a literal float name."s);
        return;
      }
      if (!j["max"].is_string()) {
        SysError::setError("SineOscillatorV3DFtry config for max: "s + j["max"].get<std::string>() + ": must be a literal float name."s);
        return;
      }
      if (!j["period"].is_string()) {
        SysError::setError("SineOscillatorV3DFtry config for period: "s + j["period"].get<std::string>() + ": must be a literal int64_t name."s);
        return;
      }
      if (!j["component"].is_string()) {
        SysError::setError("SineOscillatorV3DFtry config for period: "s + j["component"].get<std::string>() + ": must be a literal int64_t name."s);
        return;
      }

      std::string minName = j["min"].get<std::string>();
      if(!floatStore.contains(minName)) {
        SysError::setError("SineOscillatorV3Dtry config for min: "s + minName + " is not a float literal."s);
        return;
      }

      std::string maxName = j["max"].get<std::string>();
      if(!floatStore.contains(maxName)) {
        SysError::setError("SineOscillatorV3Dtry config for max: "s + maxName + " is not a float literal."s);
        return;
      }

      std::string periodName = j["period"].get<std::string>();
      if(!intStore.contains(periodName)) {
        SysError::setError("SineOscillatorV3Dtry config for period: "s + periodName + " is not a int64_t literal."s);
        return;
      }

      std::string componentName = j["component"].get<std::string>();
      if(!intStore.contains(componentName)) {
        SysError::setError("SineOscillatorV3Dtry config for period: "s + periodName + " is not a int64_t literal."s);
        return;
      }

      float min = floatStore.get(minName);
      float max = floatStore.get(maxName);
      int64_t period = intStore.get(periodName);
      int64_t component = intStore.get(componentName);
      auto so = sineOscillatorFRsrc.get("SineOscillatorV3D."s + name);

      so->setRange(min, max);
      so->setPeriod(period);
      so->setComponent(component);

    } else {
      SysError::setError("SineOscillatorV3DFtry config for "s + name + " not found."s);
    }

  }

private:

  RsrcDictionary<float>& floatStore = RsrcDictionary<float>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<Vector3D> >& behaviorRsrc = RsrcStore<Behavior<Vector3D> >::getInstance();
  RsrcStore<SineOscillatorV3D>& sineOscillatorFRsrc = RsrcStore<SineOscillatorV3D>::getInstance();
};


}  // namespace zbe

#endif  // ZBE_BEHAVIORS_SINEOSCILLATOR_H_
