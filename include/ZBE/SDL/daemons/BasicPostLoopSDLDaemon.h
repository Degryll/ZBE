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

#include "ZBE/core/system/system.h"

namespace zbe {
/** \brief Basic post-loop daemon used for SDL
 */
class ZBEAPI BasicPostLoopSDLDaemon : public Daemon {
public:
  BasicPostLoopSDLDaemon(const BasicPostLoopSDLDaemon&) = delete; //!< Avoid copy.
  void operator=(const BasicPostLoopSDLDaemon&) = delete; //!< Avoid copy.

  /** \brief Empty builder.
   */
  BasicPostLoopSDLDaemon(): window(nullptr) {}

  /** \brief Builds a BasicPostLoopSDLDaemon from a window.
   *  \param window windo to use.
   */
  BasicPostLoopSDLDaemon(std::shared_ptr<zbe::SDLWindow> window): window(window) {}

  /** \brief Destroys the BasicPostLoopSDLDaemon
   */
  ~BasicPostLoopSDLDaemon() {}

  /** \brief Sets the the window. Use with empty constructor.
   *  \param window windo to use.
   */
  void setWindow(std::shared_ptr<zbe::SDLWindow> window) {
    this->window = window;
  }

  /** \brief Runs the daemon.
   */
  void run() override {
    window->present();
  }
private:
  std::shared_ptr<zbe::SDLWindow> window;
};

}  // namespace zbe

#endif  // ZBE_SDL_DAEMONS_BASICPOSTLOOPSDLDAEMON_H_
