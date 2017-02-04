/**
 * Copyright 2012 Batis Degryll Ludo
 * @file Timer.h
 * @since 2016-03-24
 * @date 2016-04-04
 * @author Batis
 * @brief Define a timer that uses SDL to give elapsed times between events.
 */

#ifndef CORE_TOOLS_SDLTIMER_H_
#define CORE_TOOLS_SDLTIMER_H_

#include <SDL2/SDL.h>

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/core/tools/Timer.h"

namespace zbe {

/** \brief SDL implementation of Timer. Initially stopped.
 *
*/
class SDLTimer : public Timer {
  public:

    SDLTimer(bool startHere = false);

    ~SDLTimer();

    void     start();
    int64_t stop();
    void     reset();

    int64_t lapTime();
    int64_t totalTime();

    bool isRunning() {return (running);} //time is running out lalala

  protected:
    SDL_Starter &sdl;
    bool     running;          //!< True if the timer is running.
    int64_t totalElapsedTime; //!< Total time the timer has been active.
    int64_t lastTime;         //!< Time elapsed from last lap.
    int64_t lastLapTime;      //!< Stores the partial lap time when timer stops.
};

}  // namespace zbe

#endif  // CORE_TOOLS_SDLTIMER_H_
