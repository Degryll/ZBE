/**
 * Copyright 2016 Batis Degryll Ludo
 * @file SDLEventDispatcher.h
 * @since 2016-04-27
 * @date 2016-04-27
 * @author Ludo
 * @brief Dispatcher for sdl events.
 */

#ifndef SDLEVENTDISPATCHER_H
#define SDLEVENTDISPATCHER_H

#include <map>
#include <list>

#include <SDL2/SDL.h>

#include "../../io/InputBuffer.h"
#include "../../io/InputStatus.h"

namespace zbe {
class SDLEventDispatcher {
  public:
    /** Default constructor */
    SDLEventDispatcher(InputBuffer * inputBuffer) : inputBuffer(inputBuffer) {}

    /** Default destructor */
    ~SDLEventDispatcher() {}

    /** \brief Distribute SDL events in the appropriate structures of the system.
     */
    void run();
  private:
    void setState(uint32_t key, float value, uint64_t time);

    void setMouseButtonState(SDL_Event &event, float value);

    void setMouseWheelState(SDL_Event &event);

    void setMouseCoordsState(SDL_Event &event);

    uint32_t getEquivalentToSDL(SDL_Keycode k) {return (k);}

    bool tryKeyboardEvent(SDL_Event &event);

    bool tryMouseEvent(SDL_Event &event);

    InputBuffer * inputBuffer;
};
}
#endif // SDLEVENTDISPATCHER_H
