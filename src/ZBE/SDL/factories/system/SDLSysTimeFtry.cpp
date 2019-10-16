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
  timerRsrc.insert("Timer.DEFAULT"s, timer);
  sdlTimerRsrc.insert("SDLTimer.DEFAULT"s, timer);
}

void SDLSysTimeFtry::setup(std::string, uint64_t) {
  using namespace std::string_literals;
  auto timer = timerRsrc.get("Timer.DEFAULT"s);
  SysTime::getInstance()->setSystemTimer(timer);
}

} // namespace zbe
