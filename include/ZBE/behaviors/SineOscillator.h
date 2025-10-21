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
}  // namespace zbe

#endif  // ZBE_BEHAVIORS_SINEOSCILLATOR_H_
