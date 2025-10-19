/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SineOscillator.h
 * @since 2020-11-12
 * @date 2020-11-12
 * @author Degryll Ludo Batis
 * @brief Varies a value like Knight rider's leds, oscillates a float value using a sinusoidal wave.
 */

#ifndef ZBE_BEHAVIORS_SINEOSCILLATOR_H_
#define ZBE_BEHAVIORS_SINEOSCILLATOR_H_

#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "ZBE/core/system/system.h"
#include "ZBE/core/system/SysError.h"
#include "ZBE/core/behaviors/Behavior.h"
#include "ZBE/core/entities/avatars/Avatar.h"
#include "ZBE/core/tools/containers/RsrcStore.h"

#include "ZBE/factories/Factory.h"


namespace zbe {

class SineOscillatorFFtry;

/** \brief Oscillates given avatar's value.
 */
class ZBEAPI SineOscillatorF : virtual public Behavior<float> {
public:
  friend class SineOscillatorFFtry;

  /** \brief base constructor
  *   \param min Min range value
  *   \param max Max range value
  *   \param cTime Local time
  *   \param period Oscillation period
  */
  SineOscillatorF(float min, float max, int64_t period) : min(min), max(max), period(period) {}

  /** \brief Virtual destructor.
   */
  virtual ~SineOscillatorF() = default;

  /** \brief Oscillates given avatar.
  *   \param avatar avatar to oscillate
   */
  void apply(std::shared_ptr<SAvatar<float> > avatar) override;

  /** \brief sets min & max range values
  *   \param min Min range value
  *   \param max Max range value
  */
  void setRange(float min, float max) {this->min = min; this->max = max;}

  /** \brief sets period and context time to use.
  *   \param cTime Local time
  *   \param period Oscillation period
  */
  void setPeriod(int64_t period) {this->period = period;}

private:
  SineOscillatorF() : min(-1.0f), max(1.0f), period(0) {}

  float min;
  float max;
  int64_t period;
};

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

class SineOscillatorV3DFtry;

/** \brief Oscillates given avatar's value.
 */
class ZBEAPI SineOscillatorV3D : virtual public Behavior<Vector3D> {
public:
  friend class SineOscillatorV3DFtry;

  /** \brief base constructor
  *   \param min Min range value
  *   \param max Max range value
  *   \param cTime Local time
  *   \param period Oscillation period
  */
  SineOscillatorV3D(float min, float max, int64_t period, int64_t component) : min(static_cast<double>(min)), max(static_cast<double>(max)), period(period), component(component) {}

  /** \brief Virtual destructor.
   */
  virtual ~SineOscillatorV3D() = default;

  /** \brief Oscillates given avatar.
  *   \param avatar avatar to oscillate
   */
  void apply(std::shared_ptr<SAvatar<Vector3D> > avatar) override;

  /** \brief sets min & max range values
  *   \param min Min range value
  *   \param max Max range value
  */
  void setRange(float min, float max) {this->min = static_cast<double>(min); this->max = static_cast<double>(max);}

  /** \brief sets period and context time to use.
  *   \param cTime Local time
  *   \param period Oscillation period
  */
  void setPeriod(int64_t period) {this->period = period;}

  /** \brief sets component to modify.
  *   \param cTime Local time
  *   \param period Oscillation period
  */
  void setComponent(int64_t component) {
    assert(component>=0 && component<=2);
    this->component = component;
  }

private:
  SineOscillatorV3D() : min(-1.0), max(1.0), period(0), component(0) {}

  double min;
  double max;
  int64_t period;
  int64_t component;
};

/** \brief Factory for SineOscillatorV3D.
 */
class ZBEAPI SineOscillatorV3DFtry : virtual public Factory {
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
