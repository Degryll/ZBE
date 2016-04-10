/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Timer.h
 * @since 2016-03-24
 * @date 2016-03-24
 * @author Batis
 * @brief Implements a timer that uses SDL to give times elapsed between events.
 */

 #include "ZBE/core/tools/SDLTimer.h"
namespace zbe {

SDLTimer::SDLTimer(bool startHere): counting(startHere), totalElapsedTime(0), lastTime(SDL_GetTicks()), lastLapTime(0) {}

void SDLTimer::start() {
  if (counting == false) {
    counting = true;
    lastTime = SDL_GetTicks();
  }
}

uint64_t SDLTimer::stop() {
  int lastLap = 0;
  if (counting == true) {
    counting = false;
    lastLap = SDL_GetTicks() - lastTime;
    lastLapTime=lastLap;
    totalElapsedTime += lastLap;
  }
  return lastLap;
}

void SDLTimer::reset() {
  counting = false;
  totalElapsedTime = 0;
  lastLapTime = 0;
}

uint64_t SDLTimer::lapTime() {
  uint64_t lastLap = -1;
  uint64_t now = SDL_GetTicks();
  if (counting == true) {
    lastLap = lastLapTime + now - lastTime;
    lastTime = now;
    lastLapTime = 0;
    totalElapsedTime += lastLap;
  }
  return lastLap;
}

uint64_t SDLTimer::totalTime() {
  uint64_t totalElapsed;

  totalElapsed = totalElapsedTime;

  if (counting == true) {
    totalElapsed += SDL_GetTicks() - lastTime;
  }
  return totalElapsed;
}

bool SDLTimer::running() {
  return counting;
}

}
