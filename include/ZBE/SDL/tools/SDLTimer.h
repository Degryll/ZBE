/**
 * Copyright 2012 Batis Degryll Ludo
 * @file SDLTimer.h
 * @since 2016-03-24
 * @date 2017-05-11
 * @author Batis
 * @brief Implements a timer that uses SDL to give elapsed times between events.
 */

#ifndef ZBE_SDL_TOOLS_SDLTIMER_H_
#define ZBE_SDL_TOOLS_SDLTIMER_H_

#include <cstdint>

#include <SDL2/SDL.h>

#include "ZBE/core/tools/time/Timer.h"
#include "ZBE/SDL/starters/SDL_Starter.h"

#include "ZBE/core/system/system.h"

namespace zbe {

/** \brief Implements a timer that uses SDL to give elapsed times between events.
 */
class ZBEAPI SDLTimer : public Timer {
public:
  /** \brief Construct the timer.
   *  \param startHere If true, once constructed, the timer start counting. Default false.
   */
  SDLTimer(bool startHere = false);

  /** \brief Destructor Shuts down SDL timer.
   */
  ~SDLTimer();

  /** \brief Start the timer.
   */
  void start() override;

  /** \brief Stop the timer, the current count holds.
   *  \return The current time.
   */
  int64_t stop() override;

  /** \brief Stop the timer and reset to 0.
   */
  void reset() override;

  /** \brief Return the lap time.
   *  \return The time since the last call to start, stop or lapTime.
   */
  int64_t lapTime() override;

  /** \brief Return the total time, it doesn't stop the timer.
   *  \return The time since start.
   */
  int64_t totalTime() override;

  /** \brief Return True if the timer is counting.
   *  \return True if the timer is running, false otherwise.
   */
  bool isRunning() override {return (running);} //time is running out lalala

protected:
  SDL_Starter &sdl;         //!< Singleton to init SDL subsystems.
  bool     running;         //!< True if the timer is running.
  int64_t totalElapsedTime; //!< Total time the timer has been active.
  int64_t lastTime;         //!< Time elapsed from last lap.
  int64_t lastLapTime;      //!< Stores the partial lap time when timer stops.
};

}  // namespace zbe

#endif  // ZBE_SDL_TOOLS_SDLTIMER_H_
