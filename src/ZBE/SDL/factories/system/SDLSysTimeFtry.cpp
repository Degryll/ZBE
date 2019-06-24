/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLSysTimeFtry.cpp
 * @since 2019-06-19
 * @date 2019-06-19
 * @author Ludo Degryll Batis
 * @brief Configures SysTime to use and SDLTimer.
 */

#include "ZBE/SDL/factories/system/SDLSysTimeFtry.h"

namespace zbe {

void SDLSysTimeFtry::create(std::string, uint64_t) {
  using namespace std::string_literals;

  auto timer = std::make_shared<SDLTimer>(true);
  uint64_t id = timerRsrc.insert("Timer.SYSTEM"s, timer);
  sdlTimerRsrc.insert(id, timer);
  dict.insert("SDLTimer.SYSTEM"s, id);
}

void SDLSysTimeFtry::setup(std::string, uint64_t) {
  using namespace std::string_literals;

  auto cTime = sysTimeRsrc.get("SysTime.SYSTEM"s);
  auto timer = timerRsrc.get("Timer.SYSTEM"s);
  cTime->setSystemTimer(timer);
}

} // namespace zbe
