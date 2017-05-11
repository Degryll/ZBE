/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLTimer.cpp
 * @since 2016-03-24
 * @date 2017-05-11
 * @author Batis
 * @brief Implements a timer that uses SDL to give elapsed times between events.
 */

 #include "ZBE/SDL/tools/SDLTimer.h"

 #include "ZBE/core/tools/math/math.h"

namespace zbe {

/** \brief Construct the timer.
 *  \param startHere If true, once constructed, the timer start counting. Default false.
 */
SDLTimer::SDLTimer(bool startHere)
  : sdl(SDL_Starter::getInstance(SDL_INIT_TIMER)),
    running(startHere), totalElapsedTime(0),
    lastTime(SDL_GetTicks()), lastLapTime(0) {}

/** \brief Destructor.
 */
SDLTimer::~SDLTimer() {
  sdl.quitSubSystem(SDL_INIT_TIMER);
}

/** \brief Start the timer.
 */
void SDLTimer::start() {
  if (running == false) {
    running = true;
    lastTime = quantizeTime(MILITOZBETU(SDL_GetTicks()));
  }
}

/** \brief Stop the timer, the current count holds.
 *  \return The current time.
 */
int64_t SDLTimer::stop() {
  int64_t lastLap = 0;
  if (running == true) {
    running = false;
    lastLap = quantizeTime(MILITOZBETU(SDL_GetTicks()) - lastTime);
    lastLapTime=lastLap;
    totalElapsedTime += lastLap;
  }
  return lastLap;
}

/** \brief Stop the timer and reset to 0.
 */
void SDLTimer::reset() {
  running = false;
  totalElapsedTime = 0;
  lastLapTime = 0;
}

/** \brief Return the lap time.
 *  \return The time since the last call to start, stop or lapTime.
 */
int64_t SDLTimer::lapTime() {
  int64_t lastLap = -1;
  int64_t now = quantizeTime(MILITOZBETU(SDL_GetTicks()));
  if (running == true) {
    lastLap = lastLapTime + now - lastTime;
    lastTime = now;
    lastLapTime = 0;
    totalElapsedTime += lastLap;
  }
  return lastLap;
}

/** \brief Return the total time, it doesn't stop the timer.
 *  \return The time since start.
 */
int64_t SDLTimer::totalTime() {
  int64_t totalElapsed;

  totalElapsed = totalElapsedTime;

  if (running == true) {
    totalElapsed += quantizeTime(MILITOZBETU(SDL_GetTicks()) - lastTime);
  }
  return totalElapsed;
}

}  // namespace zbe
