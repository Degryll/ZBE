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
  auto cTime = avatar->getContextTime();
  float div = (static_cast<float>(cTime->getTotalTime())/static_cast<float>(period))*static_cast<float>(TAU);
  float cosine = static_cast<float>(cos(static_cast<double>(div)));
  float newVal = ((cosine+1.0f)/2.0f)*(max-min)+min;
  value->set(newVal);
}

void SineOscillatorV3D::apply(std::shared_ptr<SAvatar<Vector3D> > avatar) {
  auto value = avatar->get<1, Vector3D>();
  auto cTime = avatar->getContextTime();
  double div = ( static_cast<double>(cTime->getTotalTime())/static_cast<double>(period))*TAU;
  double cosine = cos(div);
  double newVal = ((cosine+1.0)/2.0)*(max-min)+min;
  value->get()[static_cast<std::size_t>(component)] = newVal;
}
}  // namespace zbe
