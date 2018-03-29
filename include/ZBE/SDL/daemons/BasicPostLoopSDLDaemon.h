/**
 * Copyright 2015 Batis Degryll Ludo
 * @file BasicPostLoopSDLDaemon.h
 * @since 2017-05-11
 * @date 2018-02-25
 * @author Batis Degryll Ludo
 * @brief Daemon that runs after the main loop.
 * at the end of every frame:
 * Shows the window (if double buffer changes it).
 */

#ifndef ZBE_SDL_DAEMONS_BASICPOSTLOOPSDLDAEMON_H_
#define ZBE_SDL_DAEMONS_BASICPOSTLOOPSDLDAEMON_H_

#include <memory>

#include "ZBE/core/daemons/Daemon.h"
#include "ZBE/SDL/system/SDLWindow.h"

namespace zbe {
/** \brief Basic post-loop daemon used for SDL
 */
class BasicPostLoopSDLDaemon : public Daemon {
public:
  BasicPostLoopSDLDaemon(const BasicPostLoopSDLDaemon&) = delete; //!< Avoid copy.
  void operator=(const BasicPostLoopSDLDaemon&) = delete; //!< Avoid copy.

  /** \brief Builds a BasicPostLoopSDLDaemon from a window.
   *  \param window windo to use.
   */
  BasicPostLoopSDLDaemon(std::shared_ptr<zbe::SDLWindow> window): window(window) {}

  /** \brief Destroys the BasicPostLoopSDLDaemon
   */
  ~BasicPostLoopSDLDaemon() {}

  /** \brief Runs the daemon.
   */
  void run();
private:
  std::shared_ptr<zbe::SDLWindow> window;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_BASICPOSTLOOPSDLDAEMON_H_
