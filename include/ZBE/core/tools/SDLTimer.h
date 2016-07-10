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

#include "ZBE/core/tools/Timer.h"
#include <SDL2/SDL.h>

namespace zbe {

/** \brief SDL implementation of Timer. Initially stopped.
 *
*/
class SDLTimer : public Timer {
  public:

    SDLTimer(bool startHere = false);

    ~SDLTimer() {}
    void start();
    uint64_t stop();
    void reset();

    uint64_t lapTime();
    uint64_t totalTime();

    bool running(); //time is running out lalala

  protected:
    bool counting; //!< True if the timer is running.
    uint64_t totalElapsedTime; //!< Total time the timer has been active.
    uint64_t lastTime; //!< Time elapsed from last lap.

    uint64_t lastLapTime; //!< Stores the partial lap time when timer stops.
};

}  // namespace zbe

#endif  // CORE_TOOLS_SDLTIMER_H_
