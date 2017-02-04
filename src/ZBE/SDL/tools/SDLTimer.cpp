/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Timer.h
 * @since 2016-03-24
 * @date 2016-04-04
 * @author Batis
 * @brief Implements a timer that uses SDL to give times elapsed between events.
 */

 #include "ZBE/SDL/tools/SDLTimer.h"
 #include "ZBE/core/tools/math/math.h"

namespace zbe {

SDLTimer::SDLTimer(bool startHere): sdl(SDL_Starter::getInstance(SDL_INIT_TIMER)), running(startHere), totalElapsedTime(0), lastTime(SDL_GetTicks()), lastLapTime(0) {}
SDLTimer::~SDLTimer() {sdl.quitSubSystem(SDL_INIT_TIMER);}

void SDLTimer::start() {
  if (running == false) {
    running = true;
    lastTime = roundPrecision(MILITOZBETU(SDL_GetTicks()));
  }
}

int64_t SDLTimer::stop() {
  int lastLap = 0;
  if (running == true) {
    running = false;
    lastLap = roundPrecision(MILITOZBETU(SDL_GetTicks()) - lastTime);
    lastLapTime=lastLap;
    totalElapsedTime += lastLap;
  }
  return lastLap;
}

void SDLTimer::reset() {
  running = false;
  totalElapsedTime = 0;
  lastLapTime = 0;
}

int64_t SDLTimer::lapTime() {
  int64_t lastLap = -1;
  int64_t now = roundPrecision(MILITOZBETU(SDL_GetTicks()));
  if (running == true) {
    lastLap = lastLapTime + now - lastTime;
    lastTime = now;
    lastLapTime = 0;
    totalElapsedTime += lastLap;
  }
  return lastLap;
}

int64_t SDLTimer::totalTime() {
  int64_t totalElapsed;

  totalElapsed = totalElapsedTime;

  if (running == true) {
    totalElapsed += roundPrecision(MILITOZBETU(SDL_GetTicks()) - lastTime);
  }
  return totalElapsed;
}

}
