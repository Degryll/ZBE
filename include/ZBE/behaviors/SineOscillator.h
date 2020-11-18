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

class SineOscillatorFtry;

/** \brief Oscillates given avatar's value.
 */
class SineOscillator : virtual public Behavior<float> {
public:
  friend class SineOscillatorFtry;

  /** \brief base constructor
  *   \param min Min range value
  *   \param max Max range value
  *   \param cTime Local time
  *   \param period Oscillation period
  */
  SineOscillator(float min, float max, std::shared_ptr<ContextTime> cTime, float period) : min(min), max(max), cTime(cTime), period(period) {}

  /** \brief Virtual destructor.
   */
  virtual ~SineOscillator() = default;

  /** \brief Oscillates given avatar.
  *   \param avatar avatar to oscillate
   */
  void apply(std::shared_ptr<SAvatar<float> > avatar) final;

  /** \brief sets min & max range values
  *   \param min Min range value
  *   \param max Max range value
  */
  void setRange(float min, float max) {this->min = min; this->max = max;}

  /** \brief sets period and context time to use.
  *   \param cTime Local time
  *   \param period Oscillation period
  */
  void setPeriod(std::shared_ptr<ContextTime> cTime, int64_t period) {this->cTime = cTime; this->period = period;}

private:
  SineOscillator() : min(-1.0f), max(1.0f), cTime(nullptr), period(0) {}

  float min;
  float max;
  std::shared_ptr<ContextTime> cTime;
  int64_t period;
};

/** \brief Factory for SineOscillator.
 */
class ZBEAPI SineOscillatorFtry : virtual public Factory {
public:
  /** \brief Builds a SineOscillator.
   *  \param name Name for the created SineOscillator.
   *  \param cfgId SineOscillator's configuration id.
   */
  void create(std::string name, uint64_t cfgId);

  /** \brief Setup the desired tool. The tool will be complete after this step.
   *  \param name Name of the tool.
   *  \param cfgId Tool's configuration id.
   */
  void setup(std::string name, uint64_t cfgId);

private:

  RsrcDictionary<float>& floatStore = RsrcDictionary<float>::getInstance();
  RsrcDictionary<int64_t>& intStore = RsrcDictionary<int64_t>::getInstance();
  RsrcStore<ContextTime>& cTimeRsrc = RsrcStore<ContextTime>::getInstance();
  RsrcStore<nlohmann::json>& configRsrc = RsrcStore<nlohmann::json>::getInstance();
  RsrcStore<Behavior<float> >& behaviorRsrc = RsrcStore<Behavior<float> >::getInstance();
  RsrcStore<SineOscillator>& sineOscillatorRsrc = RsrcStore<SineOscillator>::getInstance();
};

}  // namespace zbe

#endif  // ZBE_BEHAVIORS_SINEOSCILLATOR_H_
