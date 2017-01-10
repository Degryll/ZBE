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

#include "ZBE/SDL/starters/SDL_Starter.h"
#include "ZBE/core/io/InputBuffer.h"
#include "ZBE/core/io/InputStatus.h"

namespace zbe {
class SDLEventDispatcher {
  public:
    SDLEventDispatcher(SDLEventDispatcher const&)    = delete;  //!< Needed for singleton.
    void operator=(SDLEventDispatcher const&) = delete;  //!< Needed for singleton.

    /** \brief Singleton implementation.
     *  \return The only instance of the SDLEventDispatcher.
     */
    static SDLEventDispatcher& getInstance() {
      static SDLEventDispatcher instance;
      return (instance);
    }

    /** \brief Returns the InputBuffer where the input info will be written.
     *  \return The InputBuffer.
     */
    InputBuffer * getInputBuffer() {return &inputBuffer;}

    /** \brief Distribute SDL events in the appropriate structures of the system.
     */
    void run();
  private:
    SDLEventDispatcher();

    ~SDLEventDispatcher();

    void setState(uint32_t key, float value, uint64_t time);

    void setMouseButtonState(SDL_Event &event, float value);

    void setMouseWheelState(SDL_Event &event);

    void setMouseCoordsState(SDL_Event &event);

    uint32_t getEquivalentToSDL(SDL_Keycode k) {return (k);}

    bool tryKeyboardEvent(SDL_Event &event);

    bool tryMouseEvent(SDL_Event &event);

    SDL_Starter &sdl;
    InputBuffer inputBuffer;
};
}
#endif // SDLEVENTDISPATCHER_H
