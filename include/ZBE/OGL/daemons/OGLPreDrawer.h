/**
 * Copyright 2012 Batis Degryll Ludo
 * @file OGLPreDrawer.h
 * @since 2018-06-13
 * @date 2018-06-13
 * @author Ludo Degryll
 * @brief
 */

#ifndef ZBE_OGL_DAEMONS_OGLPREDRAWER_H
#define ZBE_OGL_DAEMONS_OGLPREDRAWER_H

#include <memory>

#include <cstdio>


#include "ZBE/core/tools/math/math.h"

#include "ZBE/core/system/system.h"

#include "ZBE/core/daemons/Daemon.h"

#include "ZBE/tools/graphics/Camera.h"

#include "ZBE/SDL/OGL/SDLOGLWindow.h"
#include "ZBE/SDL/events/SDLEventDispatcher.h"

namespace zbe {

/** \brief Interface for all daemons. Daemons are responsible for execute automated processes. Basically Daemons rules the world.
 */
class OGLPreDrawer : public Daemon {
public:

  OGLPreDrawer() : gProgramID(0),  cam(), sdled() {}

  /** \brief Destructor.
   */
  ~OGLPreDrawer() = default;

  /** \brief Do the actual Daemon job.
   */
  void run() override {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sdled->run();
    cam->update();
  }

  void setProgram(std::shared_ptr<SDLOGLWindow> window, uint64_t programId) {
    gProgramID = window->getShaderStore()->getShader(programId);
  }

  void setCamera(std::shared_ptr<Camera> cam) {
    this->cam = cam;
  }

  void setSDLEventDispatcher(std::shared_ptr<SDLEventDispatcher> sdled) {
    this->sdled = sdled;
  }

private:
DISABLE_DLL_WARN
  GLuint gProgramID;
  std::shared_ptr<Camera> cam;
  std::shared_ptr<SDLEventDispatcher> sdled;
DISABLE_WARNING_POP()
};

}  // namespace zbe

#endif  // ZBE_OGL_DAEMONS_OGLPREDRAWER_H
