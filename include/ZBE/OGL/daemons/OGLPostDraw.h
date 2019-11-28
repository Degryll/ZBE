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
class ZBEAPI OGLPostDraw : public Daemon {
public:

  OGLPostDraw() : window(nullptr) {}

  OGLPostDraw(std::shared_ptr<zbe::SDLOGLWindow> window) : window(window) {}

  /** \brief Destructor.
   */
  ~OGLPostDraw() {}

  /** \brief Do the actual Daemon job.
   */
  void run() {
    window->glSwap();
  }

  void setWindow(std::shared_ptr<zbe::SDLOGLWindow> window){
    this->window = window;
  }

private:
  std::shared_ptr<zbe::SDLOGLWindow> window;
};

}  // namespace zbe

#endif  // ZBE_OGLE_DAEMONS_OGLPOSTDRAW_H
