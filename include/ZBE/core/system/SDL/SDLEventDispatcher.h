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

#include "../../io/InputReader.h"
#include "../../io/SDL/SDLInputReader.h"

namespace zbe {
class SDLEventDispatcher {
  public:
    /** Default constructor */
    SDLEventDispatcher() : irinstance(SDLInputReader::getInstance()), changedIds(), states(), times() {}

    /** Default destructor */
    ~SDLEventDispatcher() {}

    /** \brief Dispatches SDL events where needed
     */
    void run();
  private:
    void setState(uint32_t key, float value, uint64_t time);

    void setMouseButtonState(SDL_Event &event, float value);

    void setMouseWheelState(SDL_Event &event);

    void setMouseCoordsState(SDL_Event &event);

    uint32_t getEquivalentToSDL(SDL_Keycode k);

    bool tryKeyboardEvent(SDL_Event &event);

    bool tryMouseEvent(SDL_Event &event);

    SDLInputReader& irinstance;

    std::list<uint32_t> changedIds;
    std::map<uint32_t, float> states;
    std::map<uint32_t, uint64_t> times;
};
}
#endif // SDLEVENTDISPATCHER_H
