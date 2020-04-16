/**
 * Copyright 2015 Batis Degryll Ludo
 * @file BasicPreLoopSDLDaemon.h
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis
 * @brief Daemon that runs before the main loop.
 * at the beginning of every frame:
 * Clears the window and captures SDL events.
 */

#ifndef ZBE_SDL_DAEMONS_BASICPRELOOPSLDDAEMON_H_
#define ZBE_SDL_DAEMONS_BASICPRELOOPSLDDAEMON_H_

#include <memory>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/SDLWindow.h"
#include "ZBE/SDL/events/SDLEventDispatcher.h"

#include "ZBE/core/system/system.h"

namespace zbe {
/** \brief
 */
class BasicPreLoopSDLDaemon : public Daemon {
public:

  BasicPreLoopSDLDaemon(const BasicPreLoopSDLDaemon&) = delete; //!< Avoid copy.
  void operator=(const BasicPreLoopSDLDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty constructor.
   */
  BasicPreLoopSDLDaemon(): window(nullptr), sdlEventDist(zbe::SDLEventDispatcher::getInstance()) {}

  /** \brief Builds a BasicPostLoopSDLDaemon from a window.
   *  \param window windo to use.
   */
  BasicPreLoopSDLDaemon(std::shared_ptr<zbe::SDLWindow> window): window(window), sdlEventDist(zbe::SDLEventDispatcher::getInstance()) {}

  /** \brief Destroys the BasicPreLoopSDLDaemon
   */
  virtual ~BasicPreLoopSDLDaemon() {}

  /** \brief Sets the window. Use with empty constructor.
   *  \param window windo to use.
   */
  void setWindow(std::shared_ptr<zbe::SDLWindow> window) {
    this->window = window;
  }

  /** \brief Runs the daemon.
   */
  inline void run() {
    window->clear();
    sdlEventDist.run();
  }

private:
  std::shared_ptr<zbe::SDLWindow> window;
  zbe::SDLEventDispatcher& sdlEventDist;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_BASICPRELOOPSLDDAEMON_H_
