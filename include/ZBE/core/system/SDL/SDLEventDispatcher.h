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
    SDLEventDispatcher();
    /** Default destructor */
    virtual ~SDLEventDispatcher();

    /** \brief Dispatches SDL events where needed
     */
    void run();
  private:
    void setState(uint32_t key, float value);

    void setMouseButtonState(SDL_Event &event, float value);

    void setMouseWheelState(SDL_Event &event);

    void setMouseCoordsState(SDL_Event &event);

    uint32_t getEquivalentToSDL(SDL_Keycode k);

    bool tryKeyboardEvent(SDL_Event &event);

    bool tryMouseEvent(SDL_Event &event);

    SDLInputReader * irinstance;

    std::list<uint32_t>* changedIds;
    std::map<uint32_t, float>* states;
};
}
#endif // SDLEVENTDISPATCHER_H
