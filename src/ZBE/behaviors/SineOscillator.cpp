/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SineOscillator.h
 * @since 2020-11-12
 * @date 2020-11-12
 * @author Degryll Ludo Batis
 * @brief Varies a value like Knight rider's leds, oscillates a float value using a sinusoidal wave.
 */
#include "ZBE/behaviors/SineOscillator.h"
#include "ZBE/core/tools/math/math.h"
#include <cstdio>

namespace zbe {

void SineOscillatorF::apply(std::shared_ptr<SAvatar<float> > avatar) {
  auto value = avatar->get<1, float>();
  float div = (cTime->getTotalTime()/(float)period)*TAU;
  float cosine = cos(div);
  float newVal = ((cosine+1.0)/2.0)*(max-min)+min;
  value->set(newVal);
}

void SineOscillatorFFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  std::shared_ptr<SineOscillatorF> so = std::shared_ptr<SineOscillatorF>(new SineOscillatorF);  // std::make_shared<SineOscillator>();
  behaviorRsrc.insert("Behavior."s + name, so);
  sineOscillatorFRsrc.insert("SineOscillatorF."s + name, so);
}

void SineOscillatorFFtry::setup(std::string name, uint64_t cfgId) {
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
    if (!j["contextTime"].is_string()) {
      SysError::setError("SineOscillatorFFtry config for contextTime: "s + j["limit"].get<std::string>() + ": must be a literal context time name."s);
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

    std::string cTimeName = j["contextTime"].get<std::string>();
    if(!cTimeRsrc.contains("ContextTime."s + cTimeName)) {
      SysError::setError("SineOscillatorFFtry config for contextTime: "s + cTimeName + " is not a context time name."s);
      return;
    }

    std::string periodName = j["period"].get<std::string>();
    if(!intStore.contains(periodName)) {
      SysError::setError("SineOscillatorFFtry config for period: "s + periodName + " is not a int64_t literal."s);
      return;
    }

    float min = floatStore.get(minName);
    float max = floatStore.get(maxName);
    std::shared_ptr<ContextTime> cTime = cTimeRsrc.get("ContextTime."s + cTimeName);
    int64_t period = intStore.get(periodName);
    auto so = sineOscillatorFRsrc.get("SineOscillatorF."s + name);

    so->setRange(min, max);
    so->setPeriod(cTime, period);

  } else {
    SysError::setError("SineOscillatorFFtry config for "s + name + " not found."s);
  }

}

void SineOscillatorV3D::apply(std::shared_ptr<SAvatar<Vector3D> > avatar) {
  auto value = avatar->get<1, Vector3D>();
  float div = (cTime->getTotalTime()/(float)period)*TAU;
  float cosine = cos(div);
  float newVal = ((cosine+1.0)/2.0)*(max-min)+min;
  value->get()[component] = newVal;
}

void SineOscillatorV3DFtry::create(std::string name, uint64_t cfgId) {
  using namespace std::string_literals;
  std::shared_ptr<SineOscillatorV3D> so = std::shared_ptr<SineOscillatorV3D>(new SineOscillatorV3D);  // std::make_shared<SineOscillator>();
  behaviorRsrc.insert("Behavior."s + name, so);
  sineOscillatorFRsrc.insert("SineOscillatorV3D."s + name, so);

}

void SineOscillatorV3DFtry::setup(std::string name, uint64_t cfgId) {
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
    if (!j["contextTime"].is_string()) {
      SysError::setError("SineOscillatorV3DFtry config for contextTime: "s + j["limit"].get<std::string>() + ": must be a literal context time name."s);
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

    std::string cTimeName = j["contextTime"].get<std::string>();
    if(!cTimeRsrc.contains("ContextTime."s + cTimeName)) {
      SysError::setError("SineOscillatorV3Dtry config for contextTime: "s + cTimeName + " is not a context time name."s);
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
    std::shared_ptr<ContextTime> cTime = cTimeRsrc.get("ContextTime."s + cTimeName);
    int64_t period = intStore.get(periodName);
    int64_t component = intStore.get(componentName);
    auto so = sineOscillatorFRsrc.get("SineOscillatorV3D."s + name);

    so->setRange(min, max);
    so->setPeriod(cTime, period);
    so->setComponent(component);

  } else {
    SysError::setError("SineOscillatorV3DFtry config for "s + name + " not found."s);
  }

}

}  // namespace zbe
