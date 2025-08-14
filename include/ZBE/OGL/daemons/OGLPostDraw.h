/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLPostDraw.h
 * @since 2018-06-13
 * @date 2018-06-13
 * @author Ludo Degryll
 * @brief
 */

#ifndef ZBE_OGLE_DAEMONS_OGLPOSTDRAW_H
#define ZBE_OGLE_DAEMONS_OGLPOSTDRAW_H

#include "ZBE/core/system/system.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"

namespace zbe {

/** \brief OGL Daemon that swap buffers after the drawers end.
 */
class OGLPostDraw : public Daemon {
public:

  OGLPostDraw() : window(nullptr) {}

  explicit OGLPostDraw(std::shared_ptr<zbe::SDLOGLWindow> window) : window(window) {}

  /** \brief Destructor.
   */
  ~OGLPostDraw() = default;

  /** \brief Do the actual Daemon job.
   */
  void run() override {
    window->glSwap();
  }

  void setWindow(std::shared_ptr<zbe::SDLOGLWindow> window) {
    this->window = window;
  }

private:
DISABLE_DLL_WARN
  std::shared_ptr<zbe::SDLOGLWindow> window;
DISABLE_WARNING_POP()
};

}  // namespace zbe

#endif  // ZBE_OGLE_DAEMONS_OGLPOSTDRAW_H
