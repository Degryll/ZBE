/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Timer.h
 * @since 2016-03-24
 * @date 2016-04-04
 * @author Batis
 * @brief Implements a timer that uses SDL to give times elapsed between events.
 */

 #include "ZBE/SDL/tools/SDLTimer.h"
namespace zbe {

SDLTimer::SDLTimer(bool startHere): sdl(SDL_Starter::getInstance(SDL_INIT_TIMER)), running(startHere), totalElapsedTime(0), lastTime(SDL_GetTicks()), lastLapTime(0) {}
SDLTimer::~SDLTimer() {sdl.quitSubSystem(SDL_INIT_TIMER);}

void SDLTimer::start() {
  if (running == false) {
    running = true;
    lastTime = SDL_GetTicks();
  }
}

uint64_t SDLTimer::stop() {
  int lastLap = 0;
  if (running == true) {
    running = false;
    lastLap = SDL_GetTicks() - lastTime;
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

uint64_t SDLTimer::lapTime() {
  uint64_t lastLap = -1;
  uint64_t now = SDL_GetTicks();
  if (running == true) {
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

  if (running == true) {
    totalElapsed += SDL_GetTicks() - lastTime;
  }
  return totalElapsed;
}

}
